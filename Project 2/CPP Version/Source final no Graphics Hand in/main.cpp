#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <iomanip>

#include "LinkList.h"
#include "Stack.h"
#include "Queue.h"

#include "Grid.h"

using namespace std;

int counter;

void assert_i(int program, int ideal, const char* msg){
    counter++;
    if(program == ideal)
        //printf("%4d - Correct - %s\n", counter, msg);
        cout << "    " <<std::setprecision(4)<<counter <<" - Correct - " << msg <<endl;
    else
        //printf("%4d - Wrong   - %s - program=%d, ideal=%d\n", counter, msg, program, ideal);
        cout<< "    " << std::setprecision(4)<<counter << " - Wrong   - " << msg << " - program=" <<program<<", ideal="<<ideal<<endl;
}

void assert_p(int pX, int pY, int iX, int iY, const char* msg){
    counter++;
    if(pX == iX && pY == iY)
        //printf("%4d - Correct - %s\n", counter, msg);
        cout << "    " <<std::setprecision(4)<<counter <<" - Correct - " << msg <<endl;
    else
        //printf("%4d - Wrong   - %s - pX=%d,pY=%d iX=%d,iY=%d\n", counter, msg, pX, pY, iX, iY);
        cout << "    " <<std::setprecision(4)<<counter<<" - Wrong   - "<<msg<<" - pX="<<pX<<",pY="<<pY<<" iX="<<iX<<",iY="<<iY<<endl;
}

int ll_check(){
    //printf("Testing Linked Lists Functions\n");
    cout << "Testing Linked Lists Functions" << endl;
    LinkList l;

    counter = 0;

    assert_i(l.size(), 0, "Check LL Size after init");
    //l.print();

    l.addFront(1, -1); assert_i(l.size(), 1, "Check LL Size after addFront");
    l.addFront(2, -2); assert_i(l.size(), 2, "Check LL Size after addFront");
    l.addFront(3, -3); assert_i(l.size(), 3, "Check LL Size after addFront");
    //l.print();

    l.addBack(4, -4); assert_i(l.size(), 4, "Check LL Size after addBack");
    l.addBack(5, -5); assert_i(l.size(), 5, "Check LL Size after addBack");
    l.addBack(6, -6); assert_i(l.size(), 6, "Check LL Size after addBack");
    //l.print();

    int x, y;
    l.getFront(x, y); 
        assert_p(x, y, 3, -3, "Check LL getFront");
        assert_i(l.size(), 5, "Check LL Size after getFront");
    l.getFront(x, y);
        assert_p(x, y, 2, -2, "Check LL getFront");
        assert_i(l.size(), 4, "Check LL Size after getFront");
    l.getFront(x, y);
        assert_p(x, y, 1, -1, "Check LL getFront");
        assert_i(l.size(), 3, "Check LL Size after getFront");
    l.getFront(x, y);
        assert_p(x, y, 4, -4, "Check LL getFront");
        assert_i(l.size(), 2, "Check LL Size after getFront");
    l.getFront(x, y);
        assert_p(x, y, 5, -5, "Check LL getFront");
        assert_i(l.size(), 1, "Check LL Size after getFront");
    l.getFront(x, y);
        assert_p(x, y, 6, -6, "Check LL getFront");
        assert_i(l.size(), 0, "Check LL Size after getFront");

    l.addBack(2, 3); assert_i(l.size(), 1, "Check LL Size after addBack on Empty List");
    l.getFront(x, y);
        assert_p(x, y, 2, 3, "Check LL getFront");
        assert_i(l.size(), 0, "Check LL Size after getFront");

}

void stack_check(){
    //printf("Testing Stack Functions\n");
    cout << "Testing Stack Functions" << endl;
	Stack s;
    assert_i(s.size(), 0, "Check Stack Size after init");

    s.push(1, -1); assert_i(s.size(), 1, "Check Stack Size after Push");
    s.push(2, -2); assert_i(s.size(), 2, "Check Stack Size after Push");
    s.push(3, -3); assert_i(s.size(), 3, "Check Stack Size after Push");

    int x, y;
    s.pop(x, y);
        assert_p(x, y, 3, -3, "Check Pop");
        assert_i(s.size(), 2, "Check Size after Pop");
    s.pop(x, y);
        assert_p(x, y, 2, -2, "Check Pop");
        assert_i(s.size(), 1, "Check Size after Pop");

    s.push(6, -6); assert_i(s.size(), 2, "Check Stack Size after Push");
    s.pop(x, y);
        assert_p(x, y, 6, -6, "Check Pop");
        assert_i(s.size(), 1, "Check Size after Pop");
    s.pop(x, y);
        assert_p(x, y, 1, -1, "Check Pop");
        assert_i(s.size(), 0, "Check Size after Pop");
}

void queue_check(){
    //printf("Testing Queue Functions\n");
    cout << "Testing Queue Functions" << endl;
    Queue q;
    assert_i(q.size(), 0, "Check Queue Size after init");

    q.enqueue(1, -1); assert_i(q.size(), 1, "Check Queue Size after Enqueue");
    q.enqueue(2, -2); assert_i(q.size(), 2, "Check Queue Size after Enqueue");
    q.enqueue(3, -3); assert_i(q.size(), 3, "Check Queue Size after Enqueue");

    int x, y;
    q.dequeue(x, y);
        assert_p(x, y, 1, -1, "Check Dequeue");
        assert_i(q.size(), 2, "Check Size after Dequeue");
    q.dequeue(x, y);
        assert_p(x, y, 2, -2, "Check Dequeue");
        assert_i(q.size(), 1, "Check Size after Dequeue");

    q.enqueue(6, -6); assert_i(q.size(), 2, "Check Queue Size after Enqueue");
    q.dequeue(x, y);
        assert_p(x, y, 3, -3, "Check Dequeue");
        assert_i(q.size(), 1, "Check Size after Dequeue");
    q.dequeue(x, y);
        assert_p(x, y, 6, -6, "Check Dequeue");
        assert_i(q.size(), 0, "Check Size after Dequeue");
}

void read_check(){
    //printf("Testing ReadWorld(...) World1\n");
    cout << "Testing ReadWorld(...) World1" << endl;
    Grid *g;
    g = ReadWorld("world1.txt");

    assert_i(g->rows, 14, "ReadWorld - Rows");
    assert_i(g->cols, 17, "ReadWorld - Cols");

    char actual[14][18]={"-----------------",
                         "|               |", 
                         "|               |", 
                         "|            G  |", 
                         "|               |", 
                         "|               |", 
                         "|               |", 
                         "|               |", 
                         "|  xxxxxxxxx    |", 
                         "|          x    |", 
                         "|   S      x    |", 
                         "|          x    |", 
                         "|               |", 
                         "-----------------"}; 

    int i,j;
    int correct = 1;
    for(i = 0; i < g->rows; i++){
        for(j = 0; j < g->cols; j++){
            if(g->data[i][j] != actual[i][j])
                correct = 0;
        }
    }
    counter++;
    if(correct){
        //printf("%4d - Correct - World1 Content\n", counter);
        cout << "    " <<std::setprecision(4)<<counter<<" - Correct - World1 Content"<<endl;
        
    }else{
        //printf("%4d - Wrong   - World1 Content\n", counter);
    	cout << "    " <<std::setprecision(4)<<counter<<" - Wrong   - World1 Content"<<endl;
    	
    }
    for(i = 0; i < g->rows; i++){
        delete[] g->data[i];
    }
    delete g->data;
    delete g;

    //printf("Testing ReadWorld(...) World2\n");
    cout << "Testing ReadWorld(...) World2" << endl;
    g = ReadWorld("world2.txt");

    assert_i(g->rows, 11, "ReadWorld - Rows");
    assert_i(g->cols, 15, "ReadWorld - Cols");

    char actual2[11][16]={"---------------",
                          "|           xG|",
                          "|           xx|",
                          "|             |",
                          "|             |",
                          "|             |",
                          "|  xxxxxxxxx  |",
                          "|          x  |",
                          "|   S      x  |",
                          "|          x  |",
                          "---------------"};

    correct = 1;
    for(i = 0; i < g->rows; i++){
        for(j = 0; j < g->cols; j++){
            if(g->data[i][j] != actual2[i][j])
                correct = 0;
        }
    }
    counter++;
    if(correct){
        //printf("%4d - Correct - World2 Content\n", counter);
        cout << "    " <<std::setprecision(4)<<counter<<" - Correct - World2 Content"<<endl;
        
    }else{
        //printf("%4d - Wrong   - World2 Content\n", counter);
    	cout << "    " <<std::setprecision(4)<<counter<<" - Wrong   - World2 Content"<<endl;
    	
    }
    for(i = 0; i < g->rows; i++){
        delete[] g->data[i];
    }
    delete g->data;
    delete g;
}

void path_check1(){
    //printf("Testing FindPath(...) on World1\n");
    cout << "Testing FindPath(...) on World1" << endl;
    Grid *g;
    g = ReadWorld("world1.txt");
    
    Search *s;
    s = FindPath(g);

    assert_i(s->Length, 20, "Shortest path length - World1");
    assert_i(s->s->size(), s->Length+1, "Stack size - World1");

    int currR, currC;
    int last_currR, last_currC;
    int continuous = 1;
    int diffR, diffC;
    int i, j;

    s->s->pop(last_currR, last_currC);

    assert_i(last_currR, 10, "Start Location (Row) - World1");
    assert_i(last_currC, 4, "Start Location (Col) - World1");
    g->data[last_currR][last_currC] = '*';

    while(s->s->size() > 0){
        s->s->pop(currR, currC);
        g->data[currR][currC] = '*';

        diffR = currR - last_currR;
        diffR *= diffR;

        diffC = currC - last_currC;
        diffC *= diffC;
        // XOR - Eith diffR or diffC should be 1, not both.
        if(!(!diffR != !diffC)){
            continuous = 0;
        }
        last_currR = currR;
        last_currC = currC;
    }

    assert_i(currR, 3, "Path Ends on Goal (Row) - World1");
    assert_i(currC, 13, "Path Ends on Goal (Col) - World1");
    assert_i(continuous, 1, "Continuous Path from source");


    int actual[14][17] = {{MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT},
                          {MAX_INT,     12,     11,     12,     13,     14,     15,     16,     17,     18,     19,     20,     21,     22,     23,     24,MAX_INT},
                          {MAX_INT,     11,     10,     11,     12,     13,     14,     15,     16,     17,     18,     19,     20,     21,     22,     23,MAX_INT},
                          {MAX_INT,     10,      9,     10,     11,     12,     13,     14,     15,     16,     17,     18,     19,     20,     21,     22,MAX_INT},
                          {MAX_INT,      9,      8,      9,     10,     11,     12,     13,     14,     15,     16,     17,     18,     19,     20,     21,MAX_INT},
                          {MAX_INT,      8,      7,      8,      9,     10,     11,     12,     13,     14,     15,     16,     17,     18,     19,     20,MAX_INT},
                          {MAX_INT,      7,      6,      7,      8,      9,     10,     11,     12,     13,     14,     15,     16,     17,     18,     19,MAX_INT},
                          {MAX_INT,      6,      5,      6,      7,      8,      9,     10,     11,     12,     13,     14,     15,     16,     17,     18,MAX_INT},
                          {MAX_INT,      5,      4,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,     14,     15,     16,     17,MAX_INT},
                          {MAX_INT,      4,      3,      2,      1,      2,      3,      4,      5,      6,      7,MAX_INT,     13,     14,     15,     16,MAX_INT},
                          {MAX_INT,      3,      2,      1,      0,      1,      2,      3,      4,      5,      6,MAX_INT,     12,     13,     14,     15,MAX_INT},
                          {MAX_INT,      4,      3,      2,      1,      2,      3,      4,      5,      6,      7,MAX_INT,     11,     12,     13,     14,MAX_INT},
                          {MAX_INT,      5,      4,      3,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12,     13,MAX_INT},
                          {MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT}};

    int correct_dist = 1;// i,j;
    // Compare Calculated Distances to Model Solution. We only check for the distances less than the path length (you can stop calculating distances when you find the goal).
    for(i = 0; i < 14; i++){
        for(j = 0; j < 17; j++){
            if(actual[i][j] < 20 && actual[i][j] != s->Distance[i][j]){
                correct_dist = 0;
            } 
        }
    }
    assert_i(correct_dist, 1, "Distance Array - World1");

    //printf("Path (Not Marked):\n");
    cout << "Path (Not Marked):" << endl;
	for(i = 0; i < 14; i++){
        for(j = 0; j < 17; j++){
            printf("%c", g->data[i][j]);
        }
        printf("\n");
    }

}

void path_check2(){
    //printf("Testing FindPath(...) on World2\n");
    cout << "Testing FindPath(...) on World2" << endl;
    int i, j;
    Grid *g;
    g = ReadWorld("world2.txt");
    
    Search *s;
    s = FindPath(g);

    assert_i(s->Length, -1, "Shortest path length - World2");
    assert_i(s->s->size(), s->Length+1, "Stack size - World2");

    int actual[11][16] = {{5000, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT},
                          {5000,      10,       9,      10,      11,      12,      13,      14,      15,      16,      17,      18, MAX_INT, MAX_INT, MAX_INT},
                          {5000,       9,       8,       9,      10,      11,      12,      13,      14,      15,      16,      17, MAX_INT, MAX_INT, MAX_INT},
                          {5000,       8,       7,       8,       9,      10,      11,      12,      13,      14,      15,      16,      17,      18, MAX_INT},
                          {5000,       7,       6,       7,       8,       9,      10,      11,      12,      13,      14,      15,      16,      17, MAX_INT},
                          {5000,       6,       5,       6,       7,       8,       9,      10,      11,      12,      13,      14,      15,      16, MAX_INT},
                          {5000,       5,       4, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT,      16,      17, MAX_INT},
                          {5000,       4,       3,       2,       1,       2,       3,       4,       5,       6,       7, MAX_INT,      17,      18, MAX_INT},
                          {5000,       3,       2,       1,       0,       1,       2,       3,       4,       5,       6, MAX_INT,      18,      19, MAX_INT},
                          {5000,       4,       3,       2,       1,       2,       3,       4,       5,       6,       7, MAX_INT,      19,      20, MAX_INT},
                          {5000, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT, MAX_INT}};

    int correct_dist = 1;
    // Compare Calculated Distances to Model Solution.
    for(i = 0; i < g->rows; i++){
        for(j = 0; j < g->cols; j++){
            if(actual[i][j] != s->Distance[i][j]){
                correct_dist = 0;
            } 
        }
    }
    assert_i(correct_dist, 1, "Distance Array - World2");
}

int main(){
    ll_check();
    stack_check();
    queue_check();

    read_check();
    path_check1();
    path_check2();
	
	
	//end and free stuff
	std::cout.flush();
	free(stdin);
	free(stdout);
	//cout << "\nPress Any Key to Exit...." << endl;
	getchar();
	//system("pause");
    return 0;
}
