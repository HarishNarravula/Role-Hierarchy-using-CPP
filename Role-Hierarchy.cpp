
#include<iostream>
// #include<bits/stdc++.h>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;
#define INT_MIN -10e5;
struct node{
	string data;
    node *parent;
	// node *left,*right;
    vector<string> users;
    vector<node *> child;
    vector<string> subUsers;
    int topUsersCnt;
};

class BST{
	unordered_map<string, node *> mpU2D;
    unordered_map<node *, vector<string>> mpD2U;
    public:

        BST(){

        }

        node* createNode(string x, node *parent){
            node *nn=new node;
            nn->data=x;
            nn->parent=parent;
            nn->topUsersCnt=0;
            // nn->left=nn->right=NULL;
            return nn;
        }


        void bfsLevelOrder(node *root){
            if(root==NULL) return;
            queue<node *> q;
            q.push(root);
            while(!q.empty()){
                int n=q.size();
                while(n>0){
                    node * p = q.front();
                    q.pop();
                    cout << p->data << " ";
                    for(int i=0;i<p->child.size();i++){
                        q.push(p->child[i]);
                    }
                    n--;
                }
                cout<<endl;
            }
        }
    
        void bfs(node *root){
            if(root==NULL) return;
            queue<node *> q;
            q.push(root);
            while(!q.empty()){
                node * p = q.front();
                q.pop();
                cout << p->data << " : ";
                for(int i=0;i<p->child.size();i++){
                    cout<<p->child[i]->data<<" ";
                    q.push(p->child[i]);
                }
                cout<<endl;
            }
        }
        
        void bfsSubUsers(node *root){//or update reverse calls in assigning user to dept time in bfsSearch()
            if(root==NULL) return;
            queue<node *> q;
            q.push(root);
            int cnt=0;
            while(!q.empty()){
                cnt++;
                int n=q.size();
                while(n>0){
                    node * p = q.front();
                    q.pop();
                    if(cnt>=2){
                        for(int i=0;i<p->users.size();i++){
                            cout<<p->users[i]<<", ";
                            root->subUsers.push_back(p->users[i]);
                        }
                    }
                    // if(p->child.size()==0){}
                    for(int i=0;i<p->child.size();i++){
                        q.push(p->child[i]);
                    }
                    n--;
                }
                // cout<<endl;
            }
            cout<<endl;
        }
    
        
    
        node* bfsSearch(node *root, string val){
            if(root==NULL) return NULL;
            queue<node *> q;
            q.push(root);
            while(!q.empty()){
                int n=q.size();
                while(n>0){
                    node * p = q.front();
                    if(p->data==val) return p;
                    q.pop();
                    // cout << p->data << " ";
                    for(int i=0;i<p->child.size();i++){
                        q.push(p->child[i]);
                    }
                    n--;
                }
                cout<<endl;
            }
            return NULL;
        }
    
    void addSubRole(node *root, string sr_name, string rr_name){
        node *rr=bfsSearch(root, rr_name);
        node *sr_node = createNode(sr_name, rr);
        if(rr==NULL){
            
        }else{
            rr->child.push_back(sr_node);
        }
    }
    
    void deleteAndTransfer(node *root, string dr_name, string tr_name){
        node *dr=bfsSearch(root, dr_name);
        node *tr=bfsSearch(root, tr_name);
        int skip=0;
        if(dr->child.size()!=0){
            for(int i=0;i<dr->child.size();i++){
                if(tr==dr->child[i]){//prevents adding tr to itself(self loop) in its child
                    // tr->child.push_back(dr->child[i]);
                    skip=1;
                    for(int i=0;i<dr->parent->child.size();i++){
                        if(dr->parent->child[i]==dr){
                            cout<<i<<endl;
                            dr->parent->child[i]=tr;
                        }
                    }
                }
                else{
                    tr->child.push_back(dr->child[i]);
                }
            }
            
            if(skip==0){
                for(int i=0;i<dr->parent->child.size();i++){
                    if(dr->parent->child[i]==dr){
                        cout<<i<<endl;
                        std::vector<node *>::iterator it = dr->parent->child.begin();
                        std::advance(it, i);
                        dr->parent->child.erase(it);//tr->child[i]=NULL;
                        // dr->parent->child.erase( dr->parent->child.begin() + 3 );
                    }
                }
            }
            
        }else{
            for(int i=0;i<dr->parent->child.size();i++){
                    if(dr->parent->child[i]==dr){
                        cout<<i<<endl;
                        std::vector<node *>::iterator it = dr->parent->child.begin();
                        std::advance(it, i);
                        dr->parent->child.erase(it);//tr->child[i]=NULL;
                        // dr->parent->child.erase( dr->parent->child.begin() + 3 );
                    }
            }
        }
        
    }
    
    void addUser(node *root, string un, string role){
        node *role_node=bfsSearch(root, role);
        role_node->users.push_back(un);//bfsUpdateUsers()
        mpU2D[un]=role_node;
        mpD2U[role_node].push_back(un);
    }
    
    void displayUsers(){
        for (auto i : mpU2D){
            cout<<i.first<<" - "<<i.second->data<<endl;
        }
    }
    
    void displayUsersWithSubUsers(node *root){
        for (auto i : mpU2D){//mpU2D.size()
            node *ro=bfsSearch(root, i.second->data);
            cout<<i.first<<" - ";
            bfsSubUsers(ro);
        }
    }
    
    void deleteUsers(node *root, string uname){
        node *dept=mpU2D[uname];
        // cout<<dept->data<<endl;
        for(int i=0;i<dept->users.size();i++){
            if(dept->users[i]==uname){
                std::vector<string>::iterator it = dept->users.begin();
                std::advance(it, i);
                dept->users.erase(it);
            }
        }
        
        mpU2D.erase(uname);
        
        for(int i=0;i<mpD2U[dept].size();i++){
            if(mpD2U[dept][i]==uname){
                std::vector<string>::iterator it = mpD2U[dept].begin();
                std::advance(it, i);
                mpD2U[dept].erase(it);
            }
        }
        
    }
    
    int bfsSearchForTopUsersCnt(node *root, string val){
            if(root==NULL) return -1;
            queue<node *> q;
            q.push(root);
            while(!q.empty()){
                int n=q.size();
                while(n>0){
                    node * p = q.front();
                    if(p->parent!=NULL)
                        p->topUsersCnt=p->parent->users.size() + p->parent->topUsersCnt;
                    if(p==mpU2D[val]) return p->topUsersCnt;
                    q.pop();
                    
                    // cout << p->data << " ";
                    for(int i=0;i<p->child.size();i++){
                        q.push(p->child[i]);
                    }
                    n--;
                }
                cout<<endl;
            }
            return -1;
        }
    
        int heightBFS(node *root){
            if(root==NULL) return -1;
            queue<node *> q;
            q.push(root);
            int height=0;
            int maxHeight=INT_MIN;
            while(!q.empty()){
                int n=q.size();
                height++;
                maxHeight=max(maxHeight, height);
                while(n>0){
                    node * p = q.front();
                    q.pop();
                    for(int i=0;i<p->child.size();i++){
                        q.push(p->child[i]);
                    }
                    n--;
                }
                
            }
            return maxHeight;
        }
    
        vector<node*> nodetorootpath(node* root,string data){
            if(root == NULL){//nullptr
                vector<node*> n;
                return n;
            }

            if(root->data==data){
                vector<node*> nn;
                nn.push_back(root);
                return nn;
            }

            for(int i=0;i<root->child.size();i++){
                vector<node*> res= nodetorootpath(root->child[i], data);
                if(res.size()>0){
                    res.push_back(root);
                    return res;
                }
            }
            vector<node*> s;
            return s;

        }
    
        void lowestCommonAncestor(node* root,string a,string b){
            if(root==NULL){//nullptr
                return;
            }
            
            vector<node*> ans1=nodetorootpath(root, mpU2D[a]->data);
            vector<node*> ans2= nodetorootpath(root, mpU2D[b]->data);
            int i=ans1.size()-1,j=ans2.size()-1;
            string lca=ans1[i]->data;
            while(i>=0 && j>=0){
                if(ans1[i]->data!=ans2[j]->data){
                    break;
                }
                lca=ans1[i]->data;
                i--;j--;
            }
            node *lc=bfsSearch(root, lca);
            // cout << mpD2U[lc][0] << endl;//print first user of tht dept
            for(int i=0;i<mpD2U[lc].size();i++){
                cout<<mpD2U[lc][i]<<endl;
            }

        }

};

int main(){
	BST o;
// 	node *root=NULL;
//     root = o.insertt(root, 1); 
//     root = o.insertt(root, 2); 
//     root = o.insertt(root, 3); 
//     root = o.insertt(root, 4); 
//     root = o.insertt(root, 5);

//     cout<<root->data<<endl;
    
//     node *root = o.createNode(10);
//     (root->child).push_back(o.createNode(2));
//     (root->child).push_back(o.createNode(34));
//     (root->child).push_back(o.createNode(56));
//     (root->child).push_back(o.createNode(100));
//     (root->child[0]->child).push_back(o.createNode(77));
//     (root->child[0]->child).push_back(o.createNode(88));
//     (root->child[2]->child).push_back(o.createNode(1));
//     (root->child[3]->child).push_back(o.createNode(7));
//     (root->child[3]->child).push_back(o.createNode(8));
//     (root->child[3]->child).push_back(o.createNode(9));
  
//     cout << "Level order traversal Before Mirroring\n";
//     o.bfs(root);
    
        string root_name;
        cout<<"Enter root role name"<<endl;
        cin>>root_name;
        node *root = o.createNode(root_name, NULL);//"na"
    
        int opr;
        
        cout<<endl;
        do{ 
            cout<<"  1. Add Sub Role."<<endl<<
              "  2. Display Roles"<<endl<<
              "  3. Delete Role."<<endl<<
              "  4. Add User."<<endl<<
              "  5. Display Users."<<endl<<
              "  6. Display Users and Sub Users."<<endl<<
              "  7. Delete User."<<endl<<
              "  8. Number of users from top"<<endl<<
              "  9. Height of role hierachy."<<endl<<
              "  10. Common boss of users"<<endl;
            
            cout<<"Enter opr no."<<endl;
            cin>>opr;
            cout<<"Operation to be performed: "<<opr<<endl;
            if(opr==1){
                string sr, rr;
                cout<<"Enter sub role name: ";
                cin>>sr;
                cout<<sr<<endl;
                cout<<"Enter reporting to role name: ";
                cin>>rr;
                cout<<rr<<endl;
                o.addSubRole(root, sr, rr);
            }else if(opr==2){
                o.bfs(root);//o.bfsLevelOrder(root)
            }else if(opr==3){
                string dr, tr;
                cout<<"Enter the role to be deleted: ";
                cin>>dr;
                cout<<dr<<endl;
                cout<<"Enter the role to be transferred: ";
                cin>>tr;
                cout<<tr<<endl;
                o.deleteAndTransfer(root, dr, tr);
            }else if(opr==4){
                string un, role;
                cout<<"Enter User Name: ";
                cin>>un;
                cout<<un<<endl;
                cout<<"Enter the role: ";
                cin>>role;
                cout<<role<<endl;
                o.addUser(root, un, role);
            }else if(opr==5){
                o.displayUsers();
            }else if(opr==6){
                o.displayUsersWithSubUsers(root);
            }else if(opr==7){
                string uname;
                cout<<"Enter username to be deleted: ";
                cin>>uname;
                cout<<uname<<endl;
                o.deleteUsers(root, uname);
                o.displayUsersWithSubUsers(root);
            }else if(opr==8){
                string valOfUser2TopRoot;
                cout<<"Enter user name: ";
                cin>>valOfUser2TopRoot;
                cout<<valOfUser2TopRoot<<endl;
                cout<<o.bfsSearchForTopUsersCnt(root, valOfUser2TopRoot)<<endl;
            }else if(opr==9){
                cout<<"Height - "<<o.heightBFS(root)<<endl;
            }else if(opr==10){//lca of n-ary tree
                string x1,x2;
                cout<<endl;
                cout<<"Enter user 1: ";
                cin>>x1;
                cout<<x1<<endl;
                cout<<"Enter user 2 :";
                cin>>x2;
                cout<<x2<<endl;
                cout<<"Top most common boss - ";
                o.lowestCommonAncestor(root, x1, x2);
                cout<<endl;
            }
            cout<<endl;
        }while(opr!=0);
        
}