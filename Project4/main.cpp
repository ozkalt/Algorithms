//
//  main.cpp
//  AOAhw4
//
//  Created by Tuğba Özkal on 18.12.2017.
//  Copyright © 2017 Tuğba Özkal. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>

#define TOTAL_LINE 30

using namespace std;

int line;

class Person{
private:
    string name;
    char gender;
    int age;
    
    Person * left;
    Person * right;
    Person * parent;
    
    bool isLeft;
    bool isBlack;
    
    friend class Tree;
};

class Tree{
private:
    Person * uncle(Person *);
    Person * readFromFile(char *);
    void insertTree(Person *);
    void rotateLeft(Person *);
    void rotateRight(Person *);
    void check(Person *);

public:
    Person * root;

    Tree();
    ~Tree();
    void insert(char *);
    void print(Person *);
};


Tree::Tree(){
    root = NULL;
}


Tree::~Tree(){
    
}


Person * Tree::readFromFile(char * filename){
    Person * book = new Person[30];
    ifstream file(filename);
    line = 0;
    
    if (!file.is_open()){
        cout << "File cannot open" << endl;
        return NULL;
    }
    else{
        int i = 0;
        string name, gender, age;
        while (file.good() && i < TOTAL_LINE){
            getline(file, name, '\t');
            book[i].name = name;
            getline(file, gender, '\t');
            book[i].gender = gender[0];
            getline(file, age, '\n');
            book[i].age = atoi(age.c_str());
            book[i].left = NULL;
            book[i].right = NULL;
            book[i].parent = NULL;
            book[i].isBlack = false;
            book[i].isLeft = false;
            //insert(&book[i]);
            //cout << "okunuyor...\t" << book[i].name << "\t" << book[i].gender << "\t" << book[i].age << endl;
            i++;
            line++;
        }
        //cout << "read from file is completed" << endl;
        file.close();
    }
    //cout << "read from file is returned" << endl;
    return book;
}


void Tree::insert(char * filename){
    Person * data = readFromFile(filename);
    cout << "reading completed." << endl;
    cout << line << endl;
    for(int i = 0; i < line; i++){
        insertTree(&data[i]);
    }
    cout << "inserting completed." << endl;
}


void Tree::insertTree(Person * data){
    if(root == NULL){
        data->isBlack = true;
        root = data;
        cout << "root ekleniyor...\t" << data->name << "\t" << data->gender << "\t" << data->age << endl;
    }
    else{
        Person * traverse, * parent;
        traverse = root;
        
        while(traverse != NULL){
            parent = traverse;
            if(data->name >= traverse->name){
                traverse = traverse->right;
                if(traverse == NULL){
                    cout << parent->name << "'e right child ekleniyor...\t" << data->name << "\t" << data->gender << "\t" << data->age << endl;
                    data->isLeft = false;
                    data->parent = parent;
                    parent->right = data;
                    break;
                }
            }
            else{
                traverse = traverse->left;
                if(traverse == NULL){
                    cout << parent->name << "'e left child ekleniyor...\t" << data->name << "\t" << data->gender << "\t" << data->age << endl;
                    data->isLeft = true;
                    data->parent = parent;
                    parent->left = data;
                    break;
                }
            }
        }
        check(data);

        if(root->isBlack == false){
            root->isBlack = true;   // root'un black olup olmadigi kontrol ediliyor. eger black degil ise black yapiliyor
        }
    }
}


Person * Tree::uncle(Person * p){
    if (p->parent->parent == NULL){
        return NULL;
    }
    else{
        if(p->parent->isLeft){
            return p->parent->parent->right;    // eger kendi left child ise uncle right child'a return eder
        }
        else{
            return p->parent->parent->left;     // eger kendi right child ise unclue left child'a return eder
        }
    }
}


void Tree::rotateLeft(Person * p){
    cout << "left rotate for " << p->name << endl;
    Person * temp = p->parent;
    if(temp == root){
        root = p;
        p->parent = NULL;
        temp->right = p->left;
        temp->left->parent = temp;
        temp->parent = p;
        p->right = temp;
        
        p->isBlack = true;
        p->right->isBlack = false;
        p->left->isLeft = true;
        p->right->isLeft = false;
    }
    else{
        // iliskili tum baglar kopartilarak rotate islemi gerceklenir.
        temp->parent->right = temp->left;
        temp->left = temp->parent;
        if(temp->parent->isLeft)    {
            temp->parent->parent->left = temp;
            temp->isLeft = true;
        }
        else    {
            temp->parent->parent->right = temp;
            temp->isLeft = false;
        }
        temp->parent = temp->parent->parent;
        temp->left->parent = temp;
    
        temp->isBlack = true;
        temp->right->isBlack = false;
        temp->left->isBlack = false;
        temp->left->isLeft = true;
        temp->right->isLeft = false;
    }
}


void Tree::rotateRight(Person * p){
    cout << "right rotate for " << p->name << endl;
    Person * temp = p->parent;
    if(temp == root){
        root = p;
        p->parent = NULL;
        temp->left = p->right;
        temp->left->parent = temp;
        temp->parent = p;
        p->right = temp;
        
        p->isBlack = true;
        p->right->isBlack = false;
        p->left->isLeft = true;
        p->right->isLeft = false;
        
    }
    else{
        // iliskili tum baglar kopartilarak rotate islemi gerceklenir.
        temp->parent->left = temp->right;
        temp->right = temp->parent;
        if(temp->parent->isLeft) {
            temp->parent->parent->left = temp;
            temp->isLeft = true;
        }
        else {
            temp->parent->parent->right = temp;
            temp->isLeft = false;
        }
        temp->parent = temp->parent->parent;
        temp->right->parent = temp;
        
        temp->isBlack = true;
        temp->right->isBlack = false;
        temp->left->isBlack = false;
        temp->left->isLeft = true;
        temp->right->isLeft = false;
    }
}


void Tree::check(Person * p){
    if(p->parent == NULL){ // parent?
        cout << p->name << " has no parent." << endl;
        return;
    }
    else if(p->parent->isBlack){ // parent == black?
        cout << p->name << " has black parent." << endl;
        return;
    }
    else{ // parent == red?
        cout << p->name << " has red parent: " << p->parent->name << endl;
        if(!uncle(p)){ // uncle?
            cout << p->name << " has no uncle: " << endl;
            if(p->isLeft && p->parent->isLeft){ // LL
                cout << p->name << " LL" << endl;
                rotateRight(p);
            }
            else if(p->isLeft && !p->parent->isLeft){ // LR
                cout << p->name << " LR" << endl;
                rotateRight(p);
                rotateLeft(p);
            }
            else if(!p->isLeft && p->parent->isLeft){ // RL
                cout << p->name << " RL" << endl;
                rotateLeft(p);
                rotateRight(p);
            }
            else if(!p->isLeft && !p->parent->isLeft){ // RR
                cout << p->name << " RR" << endl;
                rotateLeft(p);
            }
        }
        else if(uncle(p)->isBlack){ // uncle == black?
            cout << p->name << " has black uncle: " << uncle(p)->name << endl;
            if(p->isLeft && p->parent->isLeft){ // LL
                cout << p->name << " LL" << endl;
                rotateRight(p);
            }
            else if(p->isLeft && !p->parent->isLeft){ // LR
                cout << p->name << " LR" << endl;
                rotateRight(p);
                rotateLeft(p);
            }
            else if(!p->isLeft && p->parent->isLeft){ // RL
                cout << p->name << " RL" << endl;
                rotateLeft(p);
                rotateRight(p);
            }
            else if(!p->isLeft && !p->parent->isLeft){ // RR
                cout << p->name << " RR" << endl;
                rotateLeft(p);
            }
        }
        else{  // uncle == red?
            cout << p->name << " has red uncle." << uncle(p)->name << endl;
            uncle(p)->isBlack = true;
            p->parent->isBlack = true;
            p->parent->parent->isBlack = false;
            
            check(p->parent->parent);
        }
    }
    
}


void Tree::print(Person * traverse){
    cout << "(";
    if(traverse->isBlack){
        cout << "B";
    }
    else{
        cout << "R";
    }
    cout << ")" << traverse->name << "-" << traverse->age << "-" << traverse->gender << endl;
    if(traverse->left){
        print(traverse->left);
    }
    if(traverse->right){
        print(traverse->right);
    }
}


int main(int argc, const char * argv[]) {
    char filename[40] = "input.txt";
    Tree t;
    t.insert(filename);
    t.print(t.root);
    return 0;
}
