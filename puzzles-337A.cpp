#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> pieces;
    int a,b;
    int i = 0;
    string str;
    cin>>a;
    cin>>b;
    int value;
    while (i<b){
        cin>>value;
        pieces.push_back(value);
        i++;
    }
    sort(pieces.begin(),pieces.end());
    int minimum = pieces[a-1] - pieces[0];
    int diff;
    for (i = 1; i <= pieces.size() - a; ++i) {
        diff = pieces[i+a-1] - pieces[i];
        if (diff < minimum)
            minimum = diff;
    }
    cout<<minimum;
}
