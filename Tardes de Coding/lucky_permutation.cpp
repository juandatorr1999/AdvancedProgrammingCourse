#include <bits/stdc++.h>


using namespace std;

int luckyPermutation(int numbers,int k_permutation){
  vector<int> number_v,lucky_n;
  int factorial_n=numbers;

  if(numbers<=14){
    for(int j=numbers-1;j>0;j--){
      factorial_n*=j;
    }
    
    if(k_permutation>factorial_n){
      return -1;
    }
  }

  for(int i=1;i<=numbers;i++){
    number_v.push_back(i);
  }
  
  while( k_permutation>1){
    next_permutation(number_v.begin(), number_v.end());
    k_permutation--;
  }
  
  
  // for(int k=0;k<number_v.size();k++){
    
  //   cout<<number_v[k];
  // }
  lucky_n.push_back(4);
  lucky_n.push_back(7);
  lucky_n.push_back(44);
  lucky_n.push_back(47);
  lucky_n.push_back(74);
  lucky_n.push_back(77);
  lucky_n.push_back(444);
  lucky_n.push_back(447);
  lucky_n.push_back(477);
  lucky_n.push_back(474);
  lucky_n.push_back(777);
  lucky_n.push_back(744);
  lucky_n.push_back(747);
  lucky_n.push_back(774);
  
  int result;
  result=0;
  for(int l=0;l<lucky_n.size();l++){
    if(numbers>=lucky_n[l] && number_v[lucky_n[l]-1]==lucky_n[l]){
      result++;
    }
  }
  

  return result;
}

int main() {
  int numbers, k_permutation;
  cin>>numbers;
  cin>>k_permutation;
  cout<<luckyPermutation(numbers, k_permutation);
}