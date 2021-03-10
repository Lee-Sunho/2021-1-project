#include "header.h"

void InitTree(UserTree *tree){ //tree 초기화
	int recordNum;
	
	tree->root = (User *)calloc(1, sizeof(User)); //동적할당
	tree->treeCount = 0; //트리개수 초기화

	recordNum = GetUserRecordNum("user.txt"); //레코드 개수 카운트
	InputUserInfo(tree, recordNum); //자동 유저 트리 삽입
}

void InitFileList(FileList *flist){
	flist->head = (File *)malloc(sizeof(File)); //list의 head 동적할당
	flist->tail = (File *)malloc(sizeof(File)); //list의 tail 동적할당
	flist->head->next = flist->tail; //list의 head의 next에 list의 tail넣음
	flist->tail->prev = flist->head; //list의 tail의 prev에 list의 head를 넣음
	flist->head->prev = NULL; //list의 head의 prev는 null
	flist->tail->next = NULL; //list의 tail의 next는 null
	flist->count = 0; //list의 개수는 0으로 초기화
}

User *MakeNode(int type, char *id, char *password, char *name, char *email){ //노드를 생성하는 함수
	User *newNode;

	newNode = (User *)malloc(sizeof(User)); //노드 동적할당

	newNode->type = type;
	strcpy(newNode->id, id); //노드의 id에 매개변수로 온 filename넣어줌
	strcpy(newNode->password, password); //노드의 password에 매개변수로 온 filename넣어줌
	strcpy(newNode->name, name); //노드의 name에 매개변수로 온 filename넣어줌
	strcpy(newNode->email, email); //노드의 email에 매개변수로 온 filename넣어줌
	newNode->left = NULL; //null로 초기화
	newNode->right = NULL; //null로 초기화

	return newNode; //newnode를 리턴해줌
}

File *MakeFileNode(char *id, char *title, char *writer, char *content, char *date){ //노드를 생성하는 함수
	File *newNode;

	newNode = (File *)malloc(sizeof(File)); //노드 동적할당

	strcpy(newNode->id, id);
	strcpy(newNode->title, title);
	strcpy(newNode->writer, writer);
	strcpy(newNode->content, content);
	strcpy(newNode->date, date);
	newNode->next = NULL;
	newNode->prev = NULL;

	return newNode; //newnode를 리턴해줌
}

void AddTree(UserTree *tree, User *node){ //트리에 넣는 함수 자세한 설명 생략 
    User *tmp = tree->root;

    if(tree->treeCount == 0){
        tree->root = node;
        tree->treeCount++;
    }   
    else{
        while(1){
            if(strcmp(tmp->id, node->id) < 0){ 
                if(tmp->right == NULL){
                    tmp->right = node;
                    tree->treeCount++;
                    break;
                }   
                else{
                    tmp = tmp->right;
                }   
            }   
            else{
                if(tmp->left == NULL){
                    tmp->left = node;
                    tree->treeCount++;
                    break;
                }   
                else{
                    tmp = tmp->left;
                }   
            }   
        }   
    }   
}

void AddFileListNode(FileList *flist, File *node){

	if(flist->head->next == flist->tail){ //리스트에 아무것도 없을때, 맨 처음 상황
		flist->head->next = node; //head의 next에 넣어줌
		node->next = flist->tail; //넣으려는 node의 next에 tail을 넣어줌
		node->prev = flist->head; //넣으려는 node의 prev에 head를 넣어줌
		flist->tail->prev = node; //tail의 prev에 넣으려는 node를 넣어줌
	}
	else{
		flist->tail->prev->next = node; //tail의 prev에 있는 node의 next에다가 넣으려는 node를 넣어줌
		node->next = flist->tail; //넣으려는 node의 next에 tail을 넣어줌
		node->prev = flist->tail->prev; //넣으려는 node의 prev에 tail의 prev노드를 넣어줌
		flist->tail->prev = node; //tail의 prev에 넣으려는 node를 넣어줌
	}
	flist->count++; //list의 개수 증가
}

int FindFileNodeIdx(FileList *flist, char *id){ //링크드리스트에서 어느 위치에 해당하는지 알려주는 함수
	File *find;
	int count = 0;

	find = flist->head->next;
	while(find ->next != NULL){
		if(!strcmp(find->id, id)){
			return count;
		}
		count++;
		find = find->next;
	}
	return -1;
}

User *FindNode(UserTree *tree, char *id){ //트리에서 노드 찾는 함수
    User *node;

    node = tree->root;

    while(1){
        if(node == NULL){
            return NULL;
        }
        if(strcmp(node->id, id) == 0){
            return node;
        }
        else if(strcmp(node->id, id) < 0){
            node = node->right;
        }
        else{
            node = node->left;
        }
    }
}

File *FindFileNode(FileList *flist, char *id){ //파일명에 해당하는 node를 리턴해주는 함수
	File *find; //찾으려는 node

	find = flist->head->next; //find에 head의 next를 넣음
	while(find->next != NULL){ //tail이 될때까지
		if(!strcmp(find->id, id)){ //node의 파일이름과 찾으려는 파일이름이 같으면 find노드를 리턴
			return find;
		}
		find = find->next; //아니라면 다음 노드 검사
	}
	return NULL; //없다면 NULL리턴
}

void ChangeNode(User *change, int type, char *password, char *name, char *email){ //트리에서 노드 변경 함수
	int i;

	change->type = type;
	strcpy(change->password, password);
	strcpy(change->name, name);
	strcpy(change->email, email);
}

void ChangeFileNode(FileList *flist, int idx, char *title, char *content){ //링크드리스트에서 노드 변경 함수
	File *change;
	int i;

	change = flist->head->next;
	for(i = 0; i < idx; i++){
		change = change->next;
	}
	strcpy(change->title, title);
	strcpy(change->content, content);
}

void DeleteNode(UserTree *tree, char *id){ //트리에서 삭제 함수
    User *temp = tree->root;
    User *parent = tree->root;
    User *delete;

    while(strcmp(temp->id, id)){
        parent = temp;
        if(strcmp(temp->id, id) < 0){
            temp = temp->right;
        }
        else{
            temp = temp->left;
        }
    }
    delete = temp;

    if(temp->left == NULL && temp->right == NULL){
        if(parent->left){
            if(!strcmp(parent->left->id, temp->id)){
                parent->left = NULL;
                return;
            }
        }
        parent->right = NULL;
    }
    else if(temp->left != NULL && temp->right != NULL){
        temp = temp->left;
        if(temp->right == NULL){
			delete->type = temp->type;
            strcpy(delete->id, temp->id);
            strcpy(delete->password, temp->password);
            strcpy(delete->name, temp->name);
            strcpy(delete->email, temp->email);
            delete->left = temp->left;
            return;
        }
        while(1){
            if(temp->right == NULL){
				delete->type = temp->type;
            	strcpy(delete->id, temp->id);
            	strcpy(delete->password, temp->password);
            	strcpy(delete->name, temp->name);
            	strcpy(delete->email, temp->email);
				parent->right = temp->left;
                return;
            }
            else{
                parent = temp;
                temp = temp->right;
            }
        }
    }
    else{
        if(temp->right != NULL){
            if(!strcmp(parent->left->id, id)){
                parent->left = temp->right;
            }
            else{
                parent->right = temp->right;
            }
        }
        if(temp->left != NULL){
            if(!strcmp(parent->left->id, id)){
                parent->left = temp->left;
            }
            else{
                parent->right = temp->left;
            }
        }
    }
    return ;
}

void DeleteFileNode(FileList *flist, char *id){ //링크드리스트에서 삭제 함수
	File *delete;
	
	delete = flist->head->next;
	while(delete->next != NULL){
		if(!strcmp(delete->id, id)){
			delete->prev->next = delete->next;
			delete->next->prev = delete->prev;
			flist->count--;
		}
		delete = delete->next;
	}
}

int GetUserRecordNum(char *filename){ //file의 레코드 수를 구해주는 함수
	FILE *fp; //File 포인터
	int count = 0; //레코드 수를 count하기위한 변수
	int filesize = 0;

	if((fp = fopen(filename, "r+")) == NULL){ //파일 오픈
		return 0;
	}
	
	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	count = filesize/sizeof(User);
	fclose(fp);
	return count;
}

int getPostFileLine(char *filename){ //file의 라인수를 구해주는 함수
	FILE *fp; //File 포인터
	int count = 0; //라인수를 count하기위한 변수
	int filesize = 0;

	if((fp = fopen(filename, "rb+")) == NULL){ //파일 오픈
		return 0;
	}
	
	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	count = filesize/sizeof(File);
	return count;
}

void InputUserInfo(UserTree *tree, int userCount){ //트리 자동 삽입 부분
	FILE *fp;
	User *node;
	User tmp;
	int i;

	memset(&tmp, 0, sizeof(User));
	if(userCount == 0){ //파일 존재하지 않을 시
		fp = fopen("user.txt", "w+");
		node = MakeNode(1, "root", "root", "root", "root@gmail.com");
		fwrite(node, sizeof(User), 1, fp);
		AddTree(tree, node);
	}
	else{ //파일 존재할 경우
		fp = fopen("user.txt", "r+");
		for(i = 0; i < userCount; i++){
			fread(&tmp, sizeof(User), 1, fp);
			if(tmp.type == 0){
				continue;
			}
			node = MakeNode(tmp.type, tmp.id, tmp.password, tmp.name, tmp.email);
			AddTree(tree, node);
		}
	}
	fclose(fp);
}

void InputFileInfo(FileList *flist, int fileCount){ //링크드리스트 자동 삽입 함수
	FILE *fp;
	File *node;
	File tmp;
	int i;

	memset(&tmp, 0, sizeof(File));
	if(fileCount == 0){
		fp = fopen("post.txt", "wb+");
	}
	else{
		fp = fopen("post.txt", "rb+");
		for(i = 0; i < fileCount; i++){
			fread(&tmp, sizeof(File), 1, fp);
			if(tmp.id[0] == '\0'){
				continue;
			}
			node = MakeFileNode(tmp.id, tmp.title, tmp.writer, tmp.content, tmp.date);
			AddFileListNode(flist, node);
		}
	}
	fclose(fp);
}

void Preorder(User *root){ //트리 출력 함수
	if(root !=  NULL){
        printf("%-15d %-15s %-15s %-15s %s\n", root->type,
				root->id, root->password, root->name, root->email);
		Preorder(root->left);
        Preorder(root->right);
    }  
}

char *GetYear() //년도 리턴하는 함수
{
    struct tm *date;
    char *year;
    const time_t t = time(NULL);
    date = localtime(&t);

    year = (char *)malloc(sizeof(char)*10);
    if(date->tm_year-100 < 10)
        sprintf(year, "0%d", date->tm_year-100);
    else
        sprintf(year, "%d", date->tm_year-100);

    return year;
}

char *GetMonth() //월 리턴하는 함수
{
    struct tm *date;
    char *month;
    const time_t t = time(NULL);
    date = localtime(&t);

    month = (char *)malloc(sizeof(char)*10);
    if(date->tm_mon+1 < 10)
        sprintf(month, "0%d", date->tm_mon+1);
    else
        sprintf(month, "%d", date->tm_mon+1);

    return month;
}

char *GetDay() //일 리턴하는 함수
{
    struct tm *date;
    char *day;
    const time_t t = time(NULL);
    date = localtime(&t);

    day = (char *)malloc(sizeof(char)*10);
    if(date->tm_mday < 10)
        sprintf(day, "0%d", date->tm_mday);
    else
        sprintf(day, "%d", date->tm_mday);

    return day;
}

char *GetFullDate(char *year, char *month, char *day){ //년-월-일 만드는 함수
	char *date;

	date = (char *)malloc(sizeof(char)*20);
	sprintf(date, "%s-%s-%s", year, month, day);
	return date;
}
