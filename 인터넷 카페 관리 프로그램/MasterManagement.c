#include "header.h"

void ShowUsers(UserTree *tree){
	printf("*************************************\n");
	printf("**           Show Users            **\n");
	printf("*************************************\n");
	printf("%-15s %-15s %-15s %-15s %s\n","Type","ID","Password","Name","Email");
	Preorder(tree->root);
	printf("<< Press any key to go previous screen >>");
	while(getchar() != '\n');
}

void AddNewUser(UserTree *tree){
	FILE *fp;
	User *node;
	int type;
	char id[10];
	char password[20];
	char name[20];
	char email[20];
	printf("*************************************\n");
    printf("**          Add New User           **\n");
    printf("*************************************\n");
	printf("Type (1:Master, 2:General User) >> ");
	scanf("%d",&type);
	printf("ID >> ");
	scanf("%s",id);
	printf("Password >> ");
	scanf("%s",password);
	printf("Name >> ");
	scanf("%s",name);
	printf("Email >> ");
	scanf("%s",email);
	
	node = MakeNode(type,id,password,name,email);
	AddTree(tree, node);

	fp = fopen("user.txt", "r+");
	fseek(fp, sizeof(User)*(tree->treeCount), SEEK_SET);
	fwrite(node, sizeof(User), 1, fp);
	printf("New Member is added!\n");
	fclose(fp);
	printf("<< Press any key to go previous screen >>\n");
	while(getchar()!='\n');
}

void EditUser(UserTree *tree){
	FILE *fp;
	int type;
	char id[10];
	char password[20];
	char name[20];
	char email[30];

	User *node;
	User tmp;

	int i;

	memset(name, 0, 10);
	memset(password, 0 ,20);
	memset(name, 0 ,20);
	memset(email, 0 ,30);

	printf("*************************************\n");
    printf("**             Edit User           **\n");
    printf("*************************************\n");
	printf("ID >> ");
	scanf("%s", id);
	node = FindNode(tree, id);
	if(node == NULL){
		printf("Edit %s Fail!!\n",id);
	}
	else{
		printf("Edit %s's information!!\n",id);
		printf("Type >> ");
    	scanf("%d",&type);
    	printf("Password >> ");
    	scanf("%s",password);
    	printf("Name >> ");
    	scanf("%s",name);
    	printf("Email >> ");
    	scanf("%s",email);

		ChangeNode(node, type, password, name, email);

		fp = fopen("user.txt", "r+");
		for(i = 0; i<tree->treeCount; i++){
			memset(&tmp,0,sizeof(User));
			fread(&tmp,sizeof(User),1,fp);
			if(!strcmp(tmp.id, id)){
				break;
			}
		}
		memset(&tmp, 0 , sizeof(User));
		fseek(fp, sizeof(User)*i, SEEK_SET);
		fwrite(&tmp, sizeof(User), 1, fp);
		fseek(fp, sizeof(User)*i, SEEK_SET);
		fwrite(node, sizeof(User), 1, fp);
		fclose(fp);
	}
	printf("%s's information is edited!!\n",node->id);
	printf(" Press any key to go previous screen >>\n");
	while(getchar() != '\n');

}


void DeleteUser(UserTree *tree){
	FILE *fp;
	int i,idx;
	char id[10];
	char check[10];
	memset(id,0,10);
	memset(check,0,10);
	User *node;
	User tmp;

	printf("*************************************\n");
    printf("**           Delete User           **\n");
    printf("*************************************\n");
	printf("ID >> ");
	scanf("%s",id);
	node = FindNode(tree, id);
	if(node == NULL){
		printf("Delete %s Fail!!\n",id);
	}
	else{
		printf("Are you sure want to delete your account? (yes/no) >> ");
		scanf("%s", check);
		getchar();

		if(strcmp(check,"yes") != 0){
			printf("Delete %s is canceled!!\n",id);
		}
		else{
			fp = fopen("user.txt", "r+");
			for(i = 0; i<tree->treeCount; i++){
				memset(&tmp, 0, sizeof(User));
				fread(&tmp, sizeof(User), 1, fp);
				if(!strcmp(tmp.id, id)){
					break;
				}
			}
			idx = i;
			memset(&tmp, 0, sizeof(User));
			fseek(fp, sizeof(User)*idx, SEEK_SET);
			for(i=idx; i<tree->treeCount;i++){
				fwrite(&tmp,sizeof(User),1,fp);
				fread(&tmp,sizeof(User),1,fp);
				fseek(fp,sizeof(User)*i,SEEK_SET);
				fwrite(&tmp,sizeof(User),1,fp);
				memset(&tmp,0,sizeof(User));
			}
			fseek(fp,sizeof(User)*tree->treeCount,SEEK_SET);
			fwrite(&tmp,sizeof(User),1,fp);
			printf("%s's account is deleted!!\n",id);
			fclose(fp);
			DeleteNode(tree, id);
            tree->treeCount--;
		}
	}
	printf("<< Press any key to go previous screen >>\n");
	while(getchar() != '\n');

}

void ShowPost(FileList *flist){
	File *node;
	int idx = 1;
	char fileid[5];
	memset(fileid, 0, 5);
	printf("*************************************\n");
    printf("**          Show All Posts         **\n");
    printf("*************************************\n");
	node = flist->head->next;
	printf("%-5s %-5s %-20s %-10s %-15s %-20s\n","Idx","ID","Title","Writer","Content","Date");
	while(node->next!=NULL){
		if(strlen(node->content)>14){
			char content[20] = {0};
			strncat(content,node->content,12);
			strcat(content,"...");
			printf("%-5d %-5s %-20s %-10s %-15s %-20s\n",idx++, node->id, node->title, node->writer, content, node->date);
		}
		else
			printf("%-5d %-5s %-20s %-10s %-15s %-20s\n",idx++, node->id, node->title, node->writer, node->content, node->date);
		node = node->next;
	}
	printf("Choose id = ");
	scanf("%s",fileid);
	getchar();
	
	node = FindFileNode(flist,fileid);
	
	if(node == NULL){
		printf("non-exist\n");
	}
	else{
		printf("*************************************\n");
    	printf("**            Show Post            **\n");
    	printf("*************************************\n");
		printf("\n");
		printf("id = %s\n", node->id);
		printf("title = %s\n", node->title);
		printf("writer = %s\n", node->writer);
		printf("content = %s\n", node->content);
		printf("date = %s\n", node->date);
		printf("<< Press any key to go previous screen >>\n");
		while(getchar()!='\n');
	}
}

void AddPost(FileList *flist){
	FILE *fp;
	char id[5];
	char title[20];
	char content[100];
	char year[5];
	char month[5];
	char day[5];
	char date[20];

	printf("*************************************\n");
    printf("**          Add New Post           **\n");
    printf("*************************************\n");
	printf("ID >> ");
	scanf("%s",id);
	printf("TITLE >> ");
	scanf("%s",title);
	printf("CONTENT >> ");
	scanf("%s",content);

	strcpy(year,GetYear());
	strcpy(month,GetMonth());
	strcpy(day,GetDay());
	strcpy(date,GetFullDate(year,month,day));
	
	File *node = MakeFileNode(id,title,nowId,content,date);
	fp = fopen("post.txt", "r+");
    fseek(fp, sizeof(File)*flist->count, SEEK_SET);
    fwrite(node, sizeof(File), 1, fp);
    fclose(fp);
	AddFileListNode(flist,node);
	printf("<< Press any key to go previous screen >>\n");
	while(getchar() != '\n');
}

void EditPost(FileList *flist){
	FILE *fp;
	char id[5];
	char title[20];
	char content[100];
	int idx, i;
	File tmp;
	printf("*************************************\n");
    printf("**            Edit Post            **\n");
    printf("*************************************\n");
	printf("ID >> ");
	scanf("%s",id);
	getchar();
	
	File *node = FindFileNode(flist,id);
	if(node == NULL){
		printf("non-exist\n");
	}
	else{
		printf("Edit %s's post!!\n",id);
		printf("Title >> ");
		scanf("%s",title);
		printf("Content >> ");
		scanf("%s",content);
		getchar();
		
		idx = FindFileNodeIdx(flist,node->id);
		ChangeFileNode(flist, idx, title, content);

		printf("%s's post is edited!!\n",id);
		
		fp = fopen("post.txt", "r+");
        memset(&tmp, 0 , sizeof(File));
        fseek(fp, sizeof(File)*idx, SEEK_SET);
        fwrite(&tmp, sizeof(File), 1, fp);
        fseek(fp, sizeof(File)*idx, SEEK_SET);
        fwrite(node, sizeof(File), 1, fp);
		fclose(fp);
    }
	printf("<< Press any key to go previous screen >>\n");
	while(getchar() != '\n');
}

void DeletePost(FileList *flist){
	FILE *fp;
	char id[5];
	char check[5];
	memset(id,0,5);
	memset(check,0,5);
	int idx,i;
	File tmp;
	File *node;
	printf("*************************************\n");
    printf("**           Delete Post           **\n");
    printf("*************************************\n");
	printf("ID >> ");
	scanf("%s",id);
	getchar();
	printf("Are you sure want to delete post? (yes/no) >> ");
	scanf("%s",check);
	getchar();
	if(strcmp(check,"yes")!=0){
		printf("Delete Canceled\n");
	}
	else{
		node = FindFileNode(flist,id);
		if(node == NULL){
			printf("non-exist\n");
		}
		else{
			idx = FindFileNodeIdx(flist,id);
			DeleteFileNode(flist,id);
			fp = fopen("post.txt", "r+");
			memset(&tmp,0,sizeof(File));
			fseek(fp,sizeof(File)*idx,SEEK_SET);
			for(i = idx; i<flist->count; i++){
				fwrite(&tmp,sizeof(File),1,fp);
				fread(&tmp,sizeof(File),1,fp);
				fseek(fp,sizeof(File)*i,SEEK_SET);
				fwrite(&tmp,sizeof(File),1,fp);
				memset(&tmp,0,sizeof(File));
			}
			fseek(fp,sizeof(File)*flist->count,SEEK_SET);
			fwrite(&tmp,sizeof(File),1,fp);
			printf("%s's post is deleted!!\n",id);
			fclose(fp);
		}
	}
	printf("<< Press any key to go previous screen >>\n");
	while(getchar() != '\n');
}
