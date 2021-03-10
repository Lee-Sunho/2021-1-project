#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>
#include <ctype.h>

typedef struct user{
    int type; //1: 마스터, 2: 일반
	char id[10]; //아이디
	char password[20]; //비밀번호
	char name[20]; //이름
	char email[30]; //이메일
    struct user *left;
    struct user *right;
}User; //file이름을 가지고 있는 노드

typedef struct file{
	char id[5]; //고유 1~99999id
	char title[20]; //제목
	char writer[10]; //작성자
	char content[100]; //내용물
	char date[20]; //날짜
	struct file *next;
	struct file *prev;
}File;

typedef struct userTree{
	struct user *root;
	int treeCount;
}UserTree; //트리구조

typedef struct filelist{
	File *head;
	File *tail;
	int count;
}FileList; //게시글 링크드리스트

//Tree, linkedlist의 기본구조들
//User
void InitTree(UserTree *tree); //tree를 초기화해주는 함수
User *MakeNode(int type, char *id, char *password, char *name, char *email); //node를 만드는 함수
void AddTree(UserTree *tree, User *node); //tree에 node를 넣는 함수
User* FindNode(UserTree *tree, char *id); //tree에서 node를 찾는 함수
void ChangeNode(User *change, int type, char *password, char *name, char *email);
//tree에서 node를 변경하는 함수
void DeleteNode(UserTree *tree, char *id); //tree에서 node를 삭제하는 함수

//File
void InitFileList(FileList *flist); //flist를 초기화해주는 함수
File *MakeFileNode(char  *id, char *title, char *writer, char *content, char *date); //node를 만드는 함수
void AddFileListNode(FileList *flist, File *node); //linkedlist에 node를넣는 함수
int FindFileNodeIdx(FileList *flist, char *id); //linkedlist에 몇번째 위치에 존재하는지 알려주는 함수
File *FindFileNode(FileList *flist, char *id); //파일명에 해당하는 node를 리턴해주는 함수
void ChangeFileNode(FileList *flist, int idx, char *title, char *content); //노드를 변경해주는 함수
void DeleteFileNode(FileList *flist, char *id); //노드를 삭제하는 함수

//함수들
int GetUserRecordNum(char *filename); //유저파일의 레코드 수를 알려주는 함수
int getPostFileLine(char *filename); //게시물파일의 레코드 수를 알려주는 함수
void InputUserInfo(UserTree *tree, int userCount); //실행초기에 레코드 수만큼 불러와서 트리에 넣는 함수
void InputFileInfo(FileList *list, int fileCount); //실행초기에 레코드수만큼 불러와서 링크드리스트에 넣는 함수 
void Preorder(User *root); //트리 출력 함수
char *GetYear(); //년도 구해주는 함수
char *GetMonth(); //월 구해주는 함수
char *GetDay(); //일 구해주는 함수
char *GetFullDate(char *year, char *month, char *day); //년-월-일로 만들어주는 함수

//MasterManagement
//UserManagement
void ShowUsers(UserTree *tree);
void AddNewUser(UserTree *tree);
void EditUser(UserTree *tree);
void DeleteUser(UserTree *tree);
//PostManagement
void ShowPost(FileList *flist);
void AddPost(FileList *flist);
void EditPost(FileList *flist);
void DeletePost(FileList *flist);

//NormalUser
//User
void ShowNormalUsers(UserTree *tree);
void LeaveCafe(UserTree *tree);
//Post
void ShowNormalPost(FileList *list);
void AddNormalPost(FileList *flist);
void EditNormalPost(FileList *flist);
void DeleteNormalPost(FileList *flist);


//Variable
char nowId[10];
