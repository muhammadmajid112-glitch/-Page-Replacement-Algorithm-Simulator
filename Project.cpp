#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void FIFO(vector<int> pages, int capacity) {
    vector<int> frames;
    queue<int> q;
    int pageFaults = 0;

    for (int page : pages) {
        if (find(frames.begin(), frames.end(), page) == frames.end()) {
            pageFaults++;

            if (frames.size() == capacity) {
                int front = q.front();
                q.pop();
                frames.erase(find(frames.begin(), frames.end(), front));
            }

            frames.push_back(page);
            q.push(page);
        }
    }

    cout << "FIFO Page Faults: " << pageFaults << endl;
}

void LRU(vector<int> pages, int capacity) {
    vector<int> frames;
    vector<int> recent;
    int pageFaults = 0;

    for (int page : pages) {
        auto it = find(frames.begin(), frames.end(), page);

        if (it == frames.end()) {
            pageFaults++;

            if (frames.size() == capacity) {
                int lru = recent.front();
                recent.erase(recent.begin());
                frames.erase(find(frames.begin(), frames.end(), lru));
            }

            frames.push_back(page);
        } else {
            recent.erase(find(recent.begin(), recent.end(), page));
        }

        recent.push_back(page);
    }

    cout << "LRU Page Faults: " << pageFaults << endl;
}

void Optimal(vector<int> pages, int capacity) {
    vector<int> frames;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];

        if (find(frames.begin(), frames.end(), page) == frames.end()) {
            pageFaults++;

            if (frames.size() < capacity) {
                frames.push_back(page);
            } else {
                int farthest = i, index = -1;

                for (int j = 0; j < frames.size(); j++) {
                    int k;
                    for (k = i + 1; k < pages.size(); k++) {
                        if (frames[j] == pages[k]) {
                            if (k > farthest) {
                                farthest = k;
                                index = j;
                            }
                            break;
                        }
                    }

                    if (k == pages.size()) {
                        index = j;
                        break;
                    }
                }

                frames[index] = page;
            }
        }
    }

    cout << "Optimal Page Faults: " << pageFaults << endl;
}

int main() {
    int n, capacity;

    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter page reference string: ";
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    cout << "Enter number of frames: ";
    cin >> capacity;

    cout << "\n--- Page Replacement Results ---\n";
    FIFO(pages, capacity);
    LRU(pages, capacity);
    Optimal(pages, capacity);

    return 0;
}
