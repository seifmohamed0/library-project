//author : seif elden mohamed
#include <bits/stdc++.h>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/rope>
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
template<class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

using namespace std;
#define go ios::sync_with_stdio(0);cin.tie(nullptr);cout.tie(nullptr);
#define ll long long
const int mxn = 2e5 + 5 , mod = 1e9 + 7 , MOD = 1e9 + 7 , mod2 = 998244353;
struct book{
	int id , quantity;
	string name;
	multiset<string>users_of_book;
};
struct user{
	int id ;
	string name;
	multiset<string>borrowed_books;
};
bool name_cmp(book & b1 , book & b2){
	return b1.name < b2.name;
}
bool id_cmp(book & b1 , book & b2){
	return b1.id < b2.id;
}
struct books{
	book Books[mxn];
	int cnt_of_books;
	books(){
		cnt_of_books = 0;
	}
	void print_info_by_index(int index){
		if(index >= cnt_of_books){
			cout<<"this book doesn't exist"<<endl;
		}else{
			cout<<"id = "<<Books[index].id<<'\n';
			cout<<"name = "<<Books[index].name<<'\n';
			cout<<"quantity = "<<Books[index].quantity<<'\n';
		}
	}
	void print_info_by_id(int Id){
		for(int i = 0; i < cnt_of_books ; i++){
			if(Books[i].id == Id){
				 print_info_by_index(i);
				 return;
			}
		}
		cout<<"this id doesn't exist"<<endl;
	}
	void print_info_by_name(string Name){
		for(int i = 0 ;i < cnt_of_books ; i++){
			if(Books[i].name == Name){
				print_info_by_index(i);
				return;
			}
		}
		cout<<"this name doesn't exist"<<endl;
	}
	void add_book(string Name , int Id , int Quantity){
		Books[cnt_of_books].id = Id;
		Books[cnt_of_books].quantity = Quantity;
		Books[cnt_of_books++].name = Name;
	}
	bool is_prefix(string s1 , string s2){
		if((int)s1.size() > (int)s2.size())
			return false;
		for(int i = 0 ; i < (int)s1.size() ; i++){
			if(s1[i] != s2[i])
				return false;
		}
		return true;
	}
	void print_books_with_prefix(string pre){
		bool found = false;
		for(int i = 0; i < cnt_of_books ; i++){
			if(is_prefix(pre , Books[i].name)){
				cout<<Books[i].name<<" ";
				found = true;
			}
		}
		if(!found)cout<<"there is no books with prefix "<<pre;
		cout<<'\n';
	}
	void sort_by_name(){
		sort(Books , Books + cnt_of_books , name_cmp);
	}
	void sort_by_id(){
		sort(Books , Books + cnt_of_books , id_cmp);
	}
	int get_index_by_name(string name){
		for(int i = 0; i < (int)cnt_of_books ; i++){
			if(Books[i].name == name)return i;
		}
		return -1;
	}
	void borrow_book(string name_of_user , int id_of_book){
		Books[id_of_book].users_of_book.insert(name_of_user);
		Books[id_of_book].quantity--;
	}
	void return_book(string name_of_user , int id_of_book){
		Books[id_of_book].users_of_book.erase(Books[id_of_book].users_of_book.find(name_of_user));
		Books[id_of_book].quantity++;
	}
	void print_users_of_book(string name){
		int idx = get_index_by_name(name);
		if(idx == -1){
			cout<<"this book doesn't exist"<<'\n';
			return;
		}
		for(auto it : Books[idx].users_of_book)
			cout<<it<<" ";
		cout<<'\n';
	}
	int get_quantity(int idx){
		return Books[idx].quantity > 0;
	}
};
books b1;
struct users{
	user User[mxn];
	int cnt_of_users;
	users(){
		cnt_of_users = 0;
	}
	void add_user(string Name , int Id){
		User[cnt_of_users].id = Id;
		User[cnt_of_users++].name = Name;
	}
	int get_index_by_name(string name){
		for(int i = 0; i < cnt_of_users ; i++){
			if(User[i].name == name)return i;
		}
		return -1;
	}
	void borrow_book(string name_of_user , string name_of_book){
		int user_index = get_index_by_name(name_of_user);
		if(user_index == -1){
			cout<<"user doesn't exist"<<'\n';
			return;
		}
		int book_index = b1.get_index_by_name(name_of_book);
		if(book_index == -1){
			cout<<"book doesn't exist"<<'\n';
			return;
		}
		if(b1.get_quantity(book_index) == 0){
			cout<<"this book all out"<<'\n';
			return;
		}
		User[user_index].borrowed_books.insert(name_of_book);
		b1.borrow_book(name_of_user , book_index);
	}
	void return_book(string name_of_user , string name_of_book){
		int user_index = get_index_by_name(name_of_user);
		if(user_index == -1){
			cout<<"user doesn't exist"<<'\n';
			return;
		}
		int book_index = b1.get_index_by_name(name_of_book);
		if(book_index == -1){
			cout<<"book doesn't exist"<<'\n';
			return;
		}
		User[user_index].borrowed_books.erase(User[user_index].borrowed_books.find(name_of_book));
		b1.return_book(name_of_user , book_index);
	}
	void print_books_of_user(string name){
		int idx = get_index_by_name(name);
		if(idx == -1){
			cout<<"this user doesn't exist"<<'\n';
			return;
		}
		for(auto it : User[idx].borrowed_books)
			cout<<it<<" ";
		cout<<endl;
	}
};
users u1;
void print(){
	cout<<"If you want exist Enter (0)"<<'\n';
	cout<<"Books choices"<<'\n';
	cout<<"if you want add book Enter (1)"<<'\n';
	cout<<"if you want sort books by name Enter (2)"<<'\n';
	cout<<"if you want sort books by id Enter (3)"<<'\n';
	cout<<"if you want print books with some prefix Enter(4)"<<'\n';
	cout<<"if you want print users of some book Enter(5)"<<'\n';
	cout<<"User choices"<<'\n';
	cout<<"if you want add user Enter (6)"<<"\n\n";
	cout<<"if you want borrow book Enter (7)"<<'\n';
	cout<<"if you want return book Enter (8)"<<'\n';
	cout<<"if you want print books of some user Enter (9)"<<'\n';
}
void bingo(){
	cout<<"WELCOME"<<'\n';
	print();
	int c;
	while(true){
		cout<<"Enter any choice"<<'\n';
		cin>>c;
		if(c == 0){
			cout<<"Bye"<<'\n';
			break;
		}else if(c == 1){
			// add book
			cout<<"Enter the name of book"<<'\n';
			string s ; cin>> s;
			cout<<"Enter the id of book"<<'\n';
			int id ; cin>>id;
			cout<<"Enter the quantity of book"<<'\n';
			int quan ; cin>>quan;
			b1.add_book(s , id , quan);
		}else if(c == 2){
			// sort books by name
			b1.sort_by_name();
		}else if(c == 3){
			// sort books by id
			b1.sort_by_id();
		}else if(c == 4){
			// print book with prefix
			cout<<"Enter the prefix ";
			string s ;cin>>s;
			b1.print_books_with_prefix(s);
		}else if(c == 5){
			cout<<"Enter the name of book"<<'\n';
			string s ; cin>>s;
			b1.print_users_of_book(s);
		}else if(c == 6){
			//add user
			cout<<"Enter the name of user ";
			string s ; cin>>s;
			cout<<"Enter the id of user ";
			int id ; cin>>id;
			u1.add_user(s , id);
		}else if(c == 7){
			// borrow book
			cout<<"Enter the name of book ";
			string s1 ; cin>>s1;
			cout<<"Enter the name of the user ";
			string s2 ; cin>>s2;
			u1.borrow_book(s2 , s1);
		}else if(c == 8){
			// return book
			cout<<"Enter the name of book ";
			string s1 ; cin>>s1;
			cout<<"Enter the name of the user ";
			string s2 ; cin>>s2;
			u1.return_book(s2 , s1);
		}else if(c == 9){
			cout<<"Enter the name of user"<<'\n';
			string s ; cin>>s;
			u1.print_books_of_user(s);
		}else{
			cout<<"NOT VALID CHOICE"<<'\n';
		}
	}
}
int main() {
	go
#ifdef LOCAL
	freopen("input.in", "rt", stdin);
//	freopen("output.in", "wt", stdout);
#endif
	int t = 1;
	//cin>>t;
	while(t--){
		bingo();
	}
	return 0;
}

