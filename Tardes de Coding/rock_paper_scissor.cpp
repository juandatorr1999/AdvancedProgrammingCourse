#include <bits/stdc++.h>
#include<iostream>
#include<vector>
#include<algorithm>


using namespace std;

int n;
vector<int> alice_moves, bob_moves;

inline void read() {
	
}
	
inline void solve() {
	int ans1 = INT_MAX;
	vector<pair<int, int> > alice_lose;
	alice_lose.push_back({0, 0});
	alice_lose.push_back({0, 2});
	alice_lose.push_back({1, 1});
	alice_lose.push_back({1, 0});
	alice_lose.push_back({2, 2});
	alice_lose.push_back({2, 1});
  sort(alice_lose.begin(), alice_lose.end());
	do {
		vector<int> alice_moves_temp = alice_moves, bob_moves_temp = bob_moves;
		for (int i = 0; i < int(alice_lose.size()); i++) {
      int result = 0 ;
			result = min(alice_moves_temp[alice_lose[i].first], bob_moves_temp[alice_lose[i].second]);
			alice_moves_temp[alice_lose[i].first] -= result;
			bob_moves_temp[alice_lose[i].second] -= result;			
		}
		int current = min(alice_moves_temp[0], bob_moves_temp[1]) + min(alice_moves_temp[1], bob_moves_temp[2]) + min(alice_moves_temp[2], bob_moves_temp[0]);
		ans1 = min(ans1, current);
	} while(std::next_permutation(alice_lose.begin(), alice_lose.end()));
	int ans2 = min(alice_moves[0], bob_moves[1]) + min(alice_moves[1], bob_moves[2]) + min(alice_moves[2], bob_moves[0]);
	cout << ans1 << ' ' << ans2 << endl;
}

int main () {
  cin >> n;
	alice_moves.resize(3);
	bob_moves.resize(3);
	for (int i = 0; i < 3; i++) cin >> alice_moves[i];
	for (int i = 0; i < 3; i++) cin >> bob_moves[i];
  solve();
}