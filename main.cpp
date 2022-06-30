#include <bits/stdc++.h>
using namespace std;

vector <string> IDs;
map<string, int> taken;

void clear_storage(){
    IDs.clear();
    taken.clear();
}

int case_insensitive_match(string s1, string s2) {
   //convert s1 and s2 into lower case strings
   transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
   transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
   if(s1.compare(s2) == 0)
      return 1; //The strings are same
   return 0; //not matched
}

void save(int n){
    ofstream outfile;
    outfile.open("IDs.csv");
    for(int i = 0 ; i < n ; i++){
        outfile << IDs[i] << endl;
        //cout<<IDs[i]<<endl;
    }
    outfile.close();
}

void print(int n){
    for(int i = 0 ; i < n ; i++)
        cout<<IDs[i]<<endl;
}

int not_valid(string id){
    return taken[id];
}

string fix_id(int x, string letter, string num){
    if(x < 100)
        num = "0" + num;
    srand(time(0));
    int x_pos = (rand() % 4);
    if (x_pos == 0)
        num = 'X' + num;
    else if (x_pos == 3)
        num = num + 'X';
    else
        num.insert(x_pos, 1, 'X');
    return letter + num;
}

int generate_id(string letter){
    srand(time(0));
    // int x = rand()%991 + 7;
    int x = rand() % 991 + 13;

    ostringstream str1;
    str1 << x;
    string num = str1.str();
    string id = fix_id(x, letter, num);
    while(not_valid(id)){
        str1.str("");
        str1.clear();
        x = rand()%983 + 5;
        str1 << x;
        num = str1.str();
        id = fix_id(x, letter, num);
    }
    id = fix_id(x, letter, num);
    taken[id]++;
    IDs.push_back(id);
}

void generate_ids(vector <pair<int,string> > req, int total){
    for(int i = 0 ; i < req.size() ; i++){
        for(int j = 0 ; j < req[i].first ; j++){
            generate_id(req[i].second);
        }
    }
}

int read_from_file(){
    clear_storage();
    string fname = "IDs.csv";
    string line;
    int cnt = 0;
    ifstream myfile (fname);
    if(myfile.is_open()){
        while(getline(myfile,line)){
          taken[line]++;
          IDs.push_back(line);
          cnt++;
        }
        myfile.close();
    }
  else cout << "Unable to open file";
  return cnt;
}

void append_studs(int extra, vector<pair<int, string> > req){
    int cnt = read_from_file();
    generate_ids(req, extra);
    save(cnt + extra);
}

void format_and_restart(int total, vector<pair<int, string> > req){
    clear_storage();
    generate_ids(req, total);
    save(total);
}

int read_input(vector<pair<int, string> > &req){
    int number_of_schools, n, tot = 0;
    string c;
    cout<<"Enter number of schools"<<endl;
    cin>>number_of_schools;
    for(int i = 0 ; i < number_of_schools ; i++){
        cout<<"Enter the code of the school #"<<i+1<<endl;
        cin>>c;
        cout<<"Enter number of students in school #"<<i+1<<endl;
        cin>>n;
        tot += n;
        req.push_back({n, c});
    }
    return tot;
}

int main(){
    int option, total;
    vector<pair<int, string> > req;
    total = read_input(req);
    cout<<"Please choose an option"<<endl;
    cout<<"1. Format and start all over\n2. Append new student(s) to the existing students\n"<<endl;
    cin>>option;
    switch(option){
        case 1 : {
            string confirm;
            cout<<"ARE YOU SURE YOU WANT TO FORMAT THE CURRENT DATA AND ADD NEW STUDENTS?\N WRITE 'YES' TO CONFIRM!"<<endl;
            cin>>confirm;
            if(case_insensitive_match("Yes", confirm))
                format_and_restart(total, req);
            else{
                req.clear();
                total = read_input(req);
            }
            break;
        }
        case 2 : {
            append_studs(total, req);
            break;
        }
    }
    // system("new_updates.bat");
    return 0;
}
