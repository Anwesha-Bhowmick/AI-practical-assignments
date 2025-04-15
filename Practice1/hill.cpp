#include<iostream>
#include<vector>
#include<random>

using namespace std;

int calculate_conflicts(const vector<int> &state)
{
    //since the indices are distinct, thus all the queens are guaranteed to be in distinct rows
    int conflicts=0;
    int n= state.size();
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(state[i]==state[j] || abs(state[i] - state[j])==abs(i-j) || abs(state[i] + state[j])==abs(i+j))
                conflicts++;
        }
    }
    return conflicts;
}



void display(const vector<int> &state)
{
    int n= state.size();
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(state[i]==j){
                cout<<" Q ";
                continue;
            }
            cout<<" - ";
        }
        cout<<endl;
    }
}

vector<int> generate_neighbour(const vector<int> &state)
{
    random_device rd;
    mt19937 gen(rd()); //seed
    int n = state.size();
    uniform_int_distribution<> distr(0, n-1);
    int index1 = distr(gen);
    int index2 = distr(gen);
    vector<int> neighbour = state;
    swap(neighbour[index1],neighbour[index2]);
    return neighbour;
    
}

vector<int> hill(const vector<int> &start, int max_iter)
{    
    vector<int> current = start;
    int current_conflicts = calculate_conflicts(current);

    for(int i=0;i<max_iter;i++){
        vector<int> neighbour = generate_neighbour(current);
        int neighbour_conflicts = calculate_conflicts(neighbour);
        if(neighbour_conflicts<current_conflicts)
        {
            current=neighbour;
            current_conflicts = neighbour_conflicts;
            cout<<endl;
            display(current);
            cout<<endl;
        }
    }
    return current;
}

int main()
{
    int n = 8; //8 queens
    int max_iter=100;
    vector<int> start(n);//start[i]=j means queen is in ith row and jth col
    for(int i=0;i<n;i++){
        start[i]=i;
    }

    vector<int> solution = hill(start, max_iter);
    cout<<"solution: "<<endl;
    display(solution);
    return 0;  
}
