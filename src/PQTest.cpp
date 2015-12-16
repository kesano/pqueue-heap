/*
 * File: PQTest.cpp
 * ----------------
 * This is a test program for the heap-based PriorityQueue class.
 */

#include <iostream>
#include <string>
#include "console.h"
#include "pqueue.h"
#include "simpio.h"
#include "strlib.h"
#include "tokenscanner.h"
using namespace std;

/* Function prototypes */
void command(string cmd, PriorityQueue<char> & pq);
void enqueueCommand(string cmd, PriorityQueue<char> & pq);
void listCommand(PriorityQueue<char> pq);
void helpCommand();

/* Main program */

int main() {
    PriorityQueue<char> pq;
    while (true) {
        string cmd = getLine("> ");
        command(cmd, pq);
    }
    return 0;
}

/*
 * Function: listCommand
 * Usage: void listCommand();
 * --------------------------
 * Displays all values stored in the priority queue one after the other in order of
 * highest to lowest priority. This implementation leaves the internal data structure
 * of the priority queue unchanged whilst obtaining each value by calling the priority
 * queue argument by value rather than by reference.
 */

void listCommand(PriorityQueue<char> pq) {
    int count = pq.size();
    cout << "Queue:";
    for (int i = 0; i < count; i++) {
        cout << " " << pq.dequeue();
    }
    cout << endl;
}

/*
 * Function: enqueueCommand
 * Usage: void enqueueCommand(cmd, pq);
 * ------------------------------------
 * Adds the value of the given command to the priority queue. If the format
 * of command is incorrect, an error message is displayed.
 */

void enqueueCommand(string cmd, PriorityQueue<char> & pq) {
    TokenScanner scanner(cmd.substr(7));
    scanner.ignoreWhitespace();
    string value = "";
    double priority;
    int n = 0;
    while (scanner.hasMoreTokens()) {
        if (n == 0) value = scanner.nextToken();
        if (n == 1) priority = stringToDouble(scanner.nextToken());
        n++;
        if (n > 2) break;
    }
    char ch;
    if (value != "") ch = value[0];
    switch (n) {
    case 1: pq.enqueue(ch); break;
    case 2: pq.enqueue(ch, priority); break;
    default:
        cout << "Illegal enqueue format. Type \"help\" to view";
        cout << " the correct format." << endl; break;
    }
}

/*
 * Function: command
 * Usage: void command(cmd, pq);
 * -----------------------------
 * Performs the specified command on the given priority queue. If the format
 * of command is incorrect, an error message is displayed.
 */

void command(string cmd, PriorityQueue<char> & pq) {
    if (cmd == "dequeue" || cmd == "peek" || cmd == "peekPriority"
         || cmd == "list") {
        if (!pq.isEmpty()) {
            if (cmd == "dequeue") {
                cout << pq.dequeue() << endl;
            } else if (cmd == "peek") {
                cout << pq.peek() << endl;
            } else if (cmd == "peekPriority") {
                cout << pq.peekPriority() << endl;
            } else {
                listCommand(pq);
            }
        } else {
            cout << "The queue is empty" << endl;
        }
    } else if (cmd.substr(0, 7) == "enqueue") {
        enqueueCommand(cmd, pq);
    } else if (cmd == "clear") {
        pq.clear();
    } else if (cmd == "size") {
        cout << pq.size() << endl;
    } else if (cmd == "isEmpty") {
        cout << ((pq.isEmpty()) ? "true" : "false") << endl;
    } else if (cmd == "help") {
        helpCommand();
    } else {
        cout << "Undefined command: " << cmd << endl;
    }
}

/*
 * Function: helpCommand
 * ---------------------
 * Displays a list of the required commands.  If you extend this program,
 * you should add new entries to this function.
 */

void helpCommand() {
    cout << "enqueue value priority -- Enqueues value at priority" << endl;
    cout << "dequeue -- Dequeues the most urgent item" << endl;
    cout << "peek -- Peeks at the first item without removing it" << endl;
    cout << "peekPriority -- Reports the priority of the first item" << endl;
    cout << "clear -- Clears the queue" << endl;
    cout << "size -- Reports the size of the queue" << endl;
    cout << "isEmpty -- Reports whether the queue is empty" << endl;
    cout << "list -- Lists the elements of the queue" << endl;
    cout << "help -- Prints this message" << endl;
}
