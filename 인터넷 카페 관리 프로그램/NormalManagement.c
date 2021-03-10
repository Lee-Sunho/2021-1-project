#include "header.h"

void ShowNormalUsers(UserTree *tree){
	printf("*************************************\n");
    printf("**           Show Users            **\n");
  	printf("*************************************\n");
	printf("%-15s %-15s %-15s %-15s %s\n","Type","ID","Password","Name","Email");
	Preorder(tree->root);
	printf("<< Press any key to go previous screen >>");
	while(getchar() != '\n');
}

void LeaveCafe(UserTree *tree){
	FILE *fp;
	char check[10];
	User tmp;
	memset(check,0,10);
	int i, idx;
	printf("*************************************\n");
    printf("**            Leave Cafe           **\n");
    printf("*************************************\n");
	printf("Are you sure want to delete your account? (yes/no) >> ");
	scanf("%s",check);
	getchar();

	if(strcmp(check,"yes")!=0){
		printf("Canceled\n");
	}
	else{
		fp = fopen("user.txt", "r+");
		for(i = 0; i<tree->treeCount; i++){
			memset(&tmp,0,sizeof(User));
			fread(&tmp,sizeof(User),1,fp);
			if(!strcmp(tmp.id,nowId)){
				break;
			}
		}
		idx = i;
		memset(&tmp,0,sizeof(User));
		fseek(fp,sizeof(User)*idx,SEEK_SET);
		for(i=idx;i<tree->treeCount;i++){
			fwrite(&tmp,sizeof(User),1,fp);
			fread(&tmp,sizeof(User),1,fp);
			fseek(fp,sizeof(User)*i,SEEK_SET);
			fwrite(&tmp,sizeof(User),1,fp);
			memset(&tmp,0,sizeof(User));
		}
		fseek(fp,sizeof(User)*tree->treeCount,SEEK_SET);
		fwrite(&tmp,sizeof(User),1,fp);
		printf("%s's account is deleted!!\n",nowId);
		fclose(fp);
		DeleteNode(tree, nowId);
		tree->treeCount--;
	}
	printf("<< Press any key to go previous screen >>\n");
    while(getchar() != '\n');
}

void ShowNormalPost(FileList *flist){
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

void AddNormalPost(FileList *flist){
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

void EditNormalPost(FileList *flist){
	FILE *fp;
	char title[20];
	char content[100];
	File *mypost[20];
	int idx=1;
	int editidx;
	int fileidx;
	File tmp;
	File *node = flist->head->next;
	memset(title,0,20);
	memset(content,0,100);
	memset(mypost,0,20);

	printf("*************************************\n");
    printf("**            Edit Post            **\n");
    printf("*************************************\n");
	printf("%-5s %-5s %-20s %-10s %-15s %-20s\n","Idx","ID","Title","Writer","Content","Date");
	while(node->next!=NULL){
		if(!strcmp(node->writer,nowId)){
			if(strlen(node->content)>14){
            	char content[20] = {0};
            	strncat(content,node->content,12);
            	strcat(content,"...");
            	printf("%-5d %-5s %-20s %-10s %-15s %-20s\n",idx, node->id, node->title, node->writer, content, node->date);
        	}
        	else
            	printf("%-5d %-5s %-20s %-10s %-15s %-20s\n",idx, node->id, node->title, node->writer, node->content, node->date);

			mypost[idx] = node;
			idx++;
		}
		node = node->next;
	}
	while(1){
		printf("Input idx >> ");
		scanf("%d",&editidx);
		getchar();

		if(mypost[editidx] == NULL){
			printf("non-exist\n");
		}
		else{
			printf("Title >> ");
			scanf("%s",title);
			getchar();
			printf("Content >> ");
			scanf("%s",content);
			getchar();
			fileidx = FindFileNodeIdx(flist,mypost[editidx]->id);
			ChangeFileNode(flist,fileidx,title,content);
			printf("%s's post is edited!!\n",nowId);

			fp = fopen("post.txt", "r+");
        	memset(&tmp, 0 , sizeof(File));
        	fseek(fp, sizeof(File)*fileidx, SEEK_SET);
        	fwrite(&tmp, sizeof(File), 1, fp);
        	fseek(fp, sizeof(File)*fileidx, SEEK_SET);
        	fwrite(mypost[editidx], sizeof(File), 1, fp);
        	fclose(fp);
			break;
		}
	}
	printf("<< Press any key to go previous screen >>\n");
    while(getchar() != '\n');
}

void DeleteNormalPost(FileList *flist){
	FILE *fp;
	File *mypost[20];
	int deleteidx;
	int idx=1;
	int fileidx;
	int i;
	char check[5];
	File *node = flist->head->next;
	File tmp;

	memset(mypost,0,20);
	memset(check,0,5);

	printf("*************************************\n");
    printf("**           Delete Post           **\n");
    printf("*************************************\n");
    printf("%-5s %-5s %-20s %-10s %-15s %-20s\n","Idx","ID","Title","Writer","Content","Date");
    while(node->next!=NULL){
        if(!strcmp(node->writer,nowId)){
            if(strlen(node->content)>14){
                char content[20] = {0};
                strncat(content,node->content,12);
                strcat(content,"...");
                printf("%-5d %-5s %-20s %-10s %-15s %-20s\n",idx, node->id, node->title, node->writer, content, node->date);
            }
            else
                printf("%-5d %-5s %-20s %-10s %-15s %-20s\n",idx, node->id, node->title, node->writer, node->content, node->date);
			
			mypost[idx] = node;
			idx ++;
		}
		node = node->next;
	}
	while(1){
        printf("Input idx >> ");
        scanf("%d",&deleteidx);
        getchar();
		if(mypost[deleteidx] == NULL){
			printf("non-exist\n");
		}
		else{
			printf("Are you sure want to delete post? (yes/no) >> ");
			scanf("%s",check);
			getchar();
			if(strcmp(check,"yes")){
				printf("Delete Canceled\n");
			}
			else{
				fileidx = FindFileNodeIdx(flist,mypost[deleteidx]->id);
            	DeleteFileNode(flist,mypost[deleteidx]->id);
				fp = fopen("post.txt","r+");
				memset(&tmp,0,sizeof(File));
            	fseek(fp,sizeof(File)*fileidx,SEEK_SET);
            	for(i = fileidx; i<flist->count; i++){
                	fwrite(&tmp,sizeof(File),1,fp);
                	fread(&tmp,sizeof(File),1,fp);
                	fseek(fp,sizeof(File)*i,SEEK_SET);
                	fwrite(&tmp,sizeof(File),1,fp);
                	memset(&tmp,0,sizeof(File));
            	}
            	fseek(fp,sizeof(File)*flist->count,SEEK_SET);
            	fwrite(&tmp,sizeof(File),1,fp);
            	printf("%s's post is deleted!!\n",nowId);
            	fclose(fp);
			}
			break;
		}
	}
	printf("<< Press any key to go previous screen >>\n");
    while(getchar() != '\n');
}

