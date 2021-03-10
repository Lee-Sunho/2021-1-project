#include "header.h"

int CyberCafeShell(UserTree *tree);
int MasterMenu();
int NormalMenu();
int UserManagementMenu();
int BoardManagementMenu();
int UserNormalManagementMenu();
int BoardNormalManagementMenu();
int MasterManagement(UserTree *tree, FileList *flist);
int NormalManagement(UserTree *tree, FileList *flist);

int main()
{
	UserTree tree;
	FileList flist; //게시물을 관리하는 list
	FILE *fp;
	int userCount = 0;
	int fileCount = 0;
	int type = 0;
	int menu = 0;
	int masterResult = 0;
	int normalResult = 0;

	InitTree(&tree); //list를 초기화 하는 함수
	InitFileList(&flist); //flist를 초기화 하는 함수

	fileCount = getPostFileLine("post.txt");
	InputFileInfo(&flist, fileCount);
	memset(nowId, 0, 10);
	type = CyberCafeShell(&tree);

	while(1){
		switch(type){
			case 1: 
				masterResult = MasterManagement(&tree, &flist);
				if(masterResult == 3){
					return 0;
				}
				break;

			case 2:
				normalResult = NormalManagement(&tree, &flist);
				if(normalResult == 3){
					return 0;
				}
				if(normalResult == 10){
					return 0;
				}
				break;

		}

	}
}

int CyberCafeShell(UserTree *tree){
	User *user;
	char id[10];
	char password[20];

	memset(id, 0, 10);
	memset(password, 0, 20);

	system("clear");
	printf("*************************************\n");
	printf("**  Cyber Cafe Management System!! **\n");
	printf("*************************************\n");
	while(1){
		printf("ID >> ");
		scanf("%s", id);
		user = FindNode(tree, id);
		if(user != NULL){
			break;
		}
		memset(id, 0, 10);
		printf("ID Wrong!!\n\n");
	}
	strcpy(nowId, id);
	while(1){
		printf("Password >> ");
		scanf("%s", password);
		if(!strcmp(password, user->password)){
			break;
		}
		memset(password, 0, 20);
		printf("PW Wrong!!\n\n");
	}
	return user->type;
}

int MasterManagement(UserTree *tree, FileList *flist){
	int menu;
	int userMenu, boardMenu;

	while(1){
		menu = MasterMenu();
		if(menu == 1){
			userMenu = UserManagementMenu();
			switch(userMenu){
				case 1 :
					ShowUsers(tree);	
					break;
				
				case 2 :
					AddNewUser(tree);
					break;
				
				case 3 :
					EditUser(tree);
					break;
				
				case 4 :
					DeleteUser(tree);
					break;
				
				case 5 :
					break;

			}
		}
		if(menu == 2){
			boardMenu = BoardManagementMenu();
			switch(boardMenu){
				case 1 :
					ShowPost(flist);
					break;
				case 2 :
					AddPost(flist);
					break;

				case 3 :
					EditPost(flist);
					break;

				case 4 : 
					DeletePost(flist);
					break;

				case 5 :
					break;
			}
		}
		if(menu == 3){
			return menu;
		}
	}
}

int NormalManagement(UserTree *tree, FileList *flist){
	int menu;
	int userMenu, boardMenu;

	while(1){
		menu = NormalMenu();
		if(menu == 1){
			userMenu = UserNormalManagementMenu();
			switch(userMenu){
				case 1 :
					ShowNormalUsers(tree);	
					break;
				
				case 2 :
					LeaveCafe(tree);
					return 10;

				case 3 :
					break;

			}
		}
		if(menu == 2){
			boardMenu = BoardNormalManagementMenu();
			switch(boardMenu){
				case 1 :
					ShowNormalPost(flist);
					break;
				case 2 :
					AddNormalPost(flist);
					break;

				case 3 :
					EditNormalPost(flist);
					break;

				case 4 : 
					DeleteNormalPost(flist);
					break;

				case 5 :
					break;
			}
		}
		if(menu == 3){
			return menu;
		}
	}
}

int MasterMenu(){
	int menu;

	system("clear");
	printf("*************************************\n");
	printf("**          Master's Menu          **\n");
	printf("*************************************\n");
	printf("(1) User Management\n");
	printf("(2) Board Management\n");
	printf("(3) Exit\n");
	while(1){
		printf("Input Number >> ");
		scanf("%d", &menu);
		while(getchar() != '\n');
		if(menu >= 1 && menu <= 3){
			break;
		}
		printf("Wrong Num!!\n");
	}

	return menu;
}

int NormalMenu(){
	int menu;

	system("clear");
	printf("*************************************\n");
	printf("**           Normal  Menu          **\n");
	printf("*************************************\n");
	printf("(1) User Management\n");
	printf("(2) Board Management\n");
	printf("(3) Exit\n");
	while(1){
		printf("Input Number >> ");
		scanf("%d", &menu);
		while(getchar() != '\n');
		if(menu >= 1 && menu <= 3){
			break;
		}
		printf("Wrong Num!!\n");
	}

	return menu;
}

int UserManagementMenu(){
	int menu;

	system("clear");
	printf("*************************************\n");
	printf("**       User Management Menu      **\n");
	printf("*************************************\n");
	printf("(1) Show Users\n");
	printf("(2) Add New User\n");
	printf("(3) Edit User\n");
	printf("(4) Delete User\n");
	printf("(5) Exit\n");
	while(1){
		printf("Input Number >> ");
		scanf("%d", &menu);
		while(getchar() != '\n');
		if(menu >= 1 && menu <= 5){
			break;
		}
		printf("Wrong Num!!\n");
	}
	
	return menu;
}

int BoardManagementMenu(){
	int menu;

	system("clear");
	printf("*************************************\n");
	printf("**      Board Management Menu      **\n");
	printf("*************************************\n");
	printf("(1) Show Post\n");
	printf("(2) Add Post\n");
	printf("(3) Edit Post\n");
	printf("(4) Delete Post\n");
	printf("(5) Exit\n");
	while(1){
		printf("Input Number >> ");
		scanf("%d", &menu);
		while(getchar() != '\n');
		if(menu >= 1 && menu <= 5){
			break;
		}
		printf("Wrong Num!!\n");
	}
	
	return menu;
}

int UserNormalManagementMenu(){
	int menu;

	system("clear");
	printf("*************************************\n");
	printf("**       User Management Menu      **\n");
	printf("*************************************\n");
	printf("(1) Show Users\n");
	printf("(2) Leave Cafe\n");
	printf("(3) Exit\n");
	while(1){
		printf("Input Number >> ");
		scanf("%d", &menu);
		while(getchar() != '\n');
		if(menu >= 1 && menu <= 3){
			break;
		}
		printf("Wrong Num!!\n");
	}
	
	return menu;
}

int BoardNormalManagementMenu(){
	int menu;

	system("clear");
	printf("*************************************\n");
	printf("**      Board Management Menu      **\n");
	printf("*************************************\n");
	printf("(1) Show Post\n");
	printf("(2) Add Post\n");
	printf("(3) Edit Post\n");
	printf("(4) Delete Post\n");
	printf("(5) Exit\n");
	while(1){
		printf("Input Number >> ");
		scanf("%d", &menu);
		while(getchar() != '\n');
		if(menu >= 1 && menu <= 5){
			break;
		}
		printf("Wrong Num!!\n");
	}
	
	return menu;
}
