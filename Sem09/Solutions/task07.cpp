// 09. DNA Sequence
// Вариант 1 - всеки substring го пазим в hash_map с бройката - става, но хеширането на стрингове е по-бавно
// Идея 2 - Rolling Hash
// Кодираме всеки символ с числата от 0 до 3
// Пазим начален хеш = 0
// Правим map<hash int, int> - хеш и брой срещания
// За i от 0 до 9 хешираме: (4*hash + li[i]) и mp[hash]++
// За всеки следващ: hash * 4 - li[i-1] * 4^10 + li[i+9] и mp[hash]++
// If mp[hash] == 2 -> pushback

//В случая с 4 символа и максимум дължина 10, не се получават кой знае колко големи суми, 
//затова няма нужда от нищо допълнително. Ако обаче трябва да хеширате цяла дума с всички 
//букви и по-голяма дължина, понеже можете да получите твърде голямо число, може да ви се
//наложи да делите процентно на някое голямо просто число, за да не оувърфлоунете. 
//Това вече ви увеличава вероятността да получите колизия, така че допълнителният трик е 
//да направите 2 хеш таблици с 2 различни функции, които се различават само по простото
//число, на което делите.

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> st;
        double pw=pow(4,10);
        int n=s.length();
        vector<int> li(n);
        for(int i=0;i<n;i++){
            if(s[i]=='A'){
                li[i]=0;
            }
            else if(s[i]=='T'){
                li[i]=1;
            }
            else if(s[i]=='G'){
                li[i]=2;
            }
            else{
                li[i]=3;
            }
        }
        long long int hash_val=0;
        unordered_map<int,int>mp;
        for(int i=0;i<n-9;i++){
            if(i==0){
                for(int i=0;i<10;i++){
                    hash_val= 4*hash_val + li[i]; //converting to decimal number
                }
                mp[hash_val]++;
            }
            else{
                hash_val = hash_val * 4 - li[i - 1] * pw + li[i + 9]; // Finding new hash value
                mp[hash_val]++;
                if(mp[hash_val]==2){
                    st.push_back(s.substr(i,10));
                }
            }
        }
        return st;
    }
};