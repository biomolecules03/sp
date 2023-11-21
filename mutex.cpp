#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

class RW {
public:
    mutex readlock;
    mutex writelock;

    static int readcount;

    class Read {
    private:
        RW& rw; // Reference to the RW instance
    public:
        Read(RW& rw) : rw(rw) {}

        void operator()() {
            try {
                lock_guard<mutex> lock(rw.readlock);
                rw.readcount++;
                if (rw.readcount == 1) {
                    rw.writelock.lock();
                }
            } catch (exception& e) {
                cerr << e.what() << endl;
            }

            cout << "Thread " << this_thread::get_id() << " is reading." << endl;
            this_thread::sleep_for(chrono::milliseconds(2500));
            cout << "Thread " << this_thread::get_id() << " has finished reading." << endl;

            try {
                lock_guard<mutex> lock(rw.readlock);
                rw.readcount--;
                if (rw.readcount == 0) {
                    rw.writelock.unlock();
                }
            } catch (exception& e) {
                cerr << e.what() << endl;
            }
        }
    };

    class Write {
    private:
        RW& rw; // Reference to the RW instance
    public:
        Write(RW& rw) : rw(rw) {}

        void operator()() {
            try {
                rw.writelock.lock();
                cout << "Thread " << this_thread::get_id() << " is Writing." << endl;
                this_thread::sleep_for(chrono::milliseconds(1000));
                cout << "Thread " << this_thread::get_id() << " has finished writing." << endl;
                rw.writelock.unlock();
            } catch (exception& e) {
                cerr << e.what() << endl;
            }
        }
    };

    void fun() {
        Read read(*this); // Pass the instance of RW to Read
        Write write(*this); // Pass the instance of RW to Write

        cout << "Enter the number of read & write processes: ";
        int n;
        cin >> n;

        cout << "Enter the sequence: 1 for reading & 0 for writing." << endl;
        vector<int> seq(n);
        for (int i = 0; i < n; i++) {
            cin >> seq[i];
        }

        vector<thread> processes;
        for (int i = 0; i < n; i++) {
            if (seq[i] == 1) {
                processes.emplace_back(read);
            } else if (seq[i] == 0) {
                processes.emplace_back(write);
            }
        }

        for (auto& t : processes) {
            t.join();
        }
    }
};

int RW::readcount = 0;

int main() {
    RW rw;
    rw.fun();

    return 0;
}
