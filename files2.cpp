#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
struct student_node
{
	char studentname[100];
	int key;
	int *marks;
	int total_marks;
	struct student_node *next;
};


struct tree_node
{
	int key;
	int total_marks;
	struct tree_node *left, *right;
};

int check_if_string_no_is_valid_or_not(char *str)
{
	int i = 0;
	for (i = 0; str[i] != '\0' && (str[i] == '\n'||(str[i]>=48&&str[i]<=57)); i++);
	if (str[i] == '\0')
		return 1;
	else
		return 0;
}

int get_no_of_subjects_from_file(FILE *p)
{
	char str[10];
	fgets(str,100,p);
	int sum=0;
	int flag = check_if_string_no_is_valid_or_not(str);
	if (flag == 0)
		return -1;
	for (int i = 0; str[i]>=48&&str[i]<=57; i++)
	{
		sum = sum * 10 + (str[i] - 48);
	}
	return sum;
}

int check_if_subjects_string_isValid(char *str,int no_of_subjects)
{
	int count_commas = 0;
	for (int i = 0; str[i] != '\n'; i++)
	{
		if (str[i] == ','&&str[i-1]!=',')
			count_commas++;
	}
	if (count_commas == no_of_subjects - 1)
		return 1;
	return 0;
}


int separate_subject_names_to_array(char **subjects, char *str,int no_of_subjects)
{
	int successflag = check_if_subjects_string_isValid(str, no_of_subjects);
	if (successflag == 0)
		return 0;
	char temp_subject_string[100];
	int i,j, k = 0;
	int subjects_offset = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] == ','&&str[i - 1] != ',')||str[i]=='\n')
		{
			subjects[subjects_offset] = (char *)malloc((k + 3)*sizeof(char));
			j = 0;
			while (j < k)
			{
				subjects[subjects_offset][j] = temp_subject_string[j];
				j++;
			}
			subjects[subjects_offset][j] = '\0';
			k = 0;
			subjects_offset++;
		}
		else if (str[i] != ',')
		{
			temp_subject_string[k] = str[i];
			k++;
		}
	}
	return 1;
}

int get_subject_names_array(FILE *p,char **subjects,int no_of_subjects)
{
	char subjects_str[1000];
	fgets(subjects_str, 1000, p);
	int success_flag=separate_subject_names_to_array(subjects, subjects_str,no_of_subjects);
	return success_flag;
}


int check_studentname_isValid(char *str)
{
	int i;
	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] >= 48 && str[i] <= 57) || (str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
		{
		}
		else if (str[i] == '\n')
		{
			str[i] = '\0';
		}
		else{
			return 0;
		}
	}
	return 1;
}

int move_file_pointer_to_previous_line(FILE *p)
{
	int slash_n_count = 0;
	char ch;
	fseek(p, -3, 1);
	while (slash_n_count < 2)
	{
		
		ch = fgetc(p);
		if (ch == '\n')
		{
			slash_n_count++;
		}
		fseek(p, -2, 1);
	}
	fseek(p, +2, 1);
	return 0;
}

int check_studentmarks_isValid(char *str)
{
	int i = 0;
	for (i = 0; str[i] != '\0'&&str[i] != '\n'; i++)
	{
		if (!((str[i] >= 48 && str[i] <= 57) || str[i] == ','))
		{
			//printf("%c", str[i]);
			return 0;
		}
	}
	return 1;
}

int modify_marks_Array_to_no_marks(int *Marks_Array, int no_of_subjects)
{
	//Marks_Array = (int *)malloc((no_of_subjects + 1)*sizeof(int));
	for (int i = 0; i < no_of_subjects; i++)
	{
		Marks_Array[i] = -1;
	}
	return 1;
}

int convert_from_string_to_int(char *str)
{
	int sum = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		sum = sum * 10 + (str[i] - 48);
	}
	return sum;
}

int modify_marks_Array_to_original_marks(char *str, int *marks, int no_of_subjects)
{
	char temp_mark[10];
	int k = 0;
	int marks_offset = 0;
	for (int i = 0; str[i] != '\0'&&marks_offset<no_of_subjects; i++)
	{
		if ((str[i] == ','&&str[i - 1] != ',')||str[i]=='\n')
		{
			temp_mark[k] = '\0';
			int mark=convert_from_string_to_int(temp_mark);
			marks[marks_offset] = mark; 
			k = 0;
			marks_offset++;
		}
		else{
			temp_mark[k] = str[i];
			k++;
		}
	}
	if (k > 0)
	{
		temp_mark[k] = '\0';
		marks[marks_offset] = convert_from_string_to_int(temp_mark);
		marks_offset++;
	}
	for (; marks_offset < no_of_subjects; marks_offset++)
	{
		marks[marks_offset] = -1;
	}
	return 1;
}

int calculate_sum_of_marks(int *marks, int no_of_students)
{
	int total = 0;
	for (int i = 0; i < no_of_students; i++)
	{
		if (marks[i] != -1)
			total = total + marks[i];
	}
	return total;
}

struct student_node * createStudentNode(char *studentname,int key, int *marksArray, int total)
{
	struct student_node *newNode = (struct student_node *)malloc(sizeof(struct student_node));
	strcpy_s(newNode->studentname, studentname);
	newNode->key = key;
	newNode->marks = marksArray;
	newNode->total_marks = total;
	newNode->next = NULL;
	return newNode;
}

struct student_node * AddStudentsNode(struct student_node *root,char *studentname, int key, int *marksArray, int total)
{
	if (root == NULL)
		return createStudentNode(studentname,key, marksArray, total);
	struct student_node *temp = createStudentNode(studentname,key, marksArray, total);
	temp->next = root;
	return temp;
}

struct student_node * Reverse_student_SLL(struct student_node *root)
{
	if (root == NULL)
		return NULL;
	struct student_node *temp;
	if (root->next == NULL)
	{
		return root;
	}
	else{
		temp = Reverse_student_SLL(root->next);
		root->next->next = root;
		root->next = NULL;
		return temp;
	}
}

void print_student_node_SLL(struct student_node *root, int no_of_subjects)
{
	while (root != NULL)
	{
		printf("%d\t", root->key);
		printf("%15s\t", root->studentname);
		for (int i = 0; i < no_of_subjects; i++)
			printf("\t%d", root->marks[i]);
		printf("\t%d\n", root->total_marks);
		root = root->next;
	}
}


struct student_node * create_students_SLL_from_file(FILE *p, int no_of_subjects)
{
	char student_name[100];
	char student_marks[500];
	int *marksArray=NULL;
	int key = 1;
	struct student_node *root = NULL;
	while (!feof(p))
	{
		fgets(student_name, 100, p);
		fgets(student_marks, 500, p);
		int successflag = check_studentname_isValid(student_name);
		if (successflag == 0)
		{
			strcpy_s(student_marks, student_name);
			strcpy_s(student_name, "NoStudentName");
			move_file_pointer_to_previous_line(p);
		}
		successflag = check_studentmarks_isValid(student_marks);
		marksArray = (int *)malloc((no_of_subjects+1)*sizeof(int));
		if (successflag == 0)
		{
			modify_marks_Array_to_no_marks(marksArray, no_of_subjects);
			move_file_pointer_to_previous_line(p);
		}
		else{
			modify_marks_Array_to_original_marks(student_marks, marksArray, no_of_subjects);
		}
		int sum = calculate_sum_of_marks(marksArray, no_of_subjects);
		root = AddStudentsNode(root,student_name,key, marksArray, sum);
		key++;
	}
	root = Reverse_student_SLL(root);
	return root;
}

int count_no_of_students(struct student_node *root)
{
	int count = 0;
	while (root != NULL)
	{
		count++;
		root = root->next;
	}
	return count;
}

void copy_pointers_to_array(struct student_node **Arr, struct student_node *head)
{
	int i = 0;
	while (head != NULL)
	{
		Arr[i] =head;
		head = head->next;
		i++;
	}
}

struct student_node * search_by_key_and_return_pointer(struct student_node **Arr, int key,int count)
{
	if (key > count)
		return NULL;
	struct student_node *node = Arr[key - 1];
	//printf("In the function\t%s", node->studentname);
	return Arr[key - 1];
}

struct tree_node * create_tree_node(int k, int totalmarks)
{
	struct tree_node *newNode = (struct tree_node *)malloc(sizeof(struct tree_node));
	newNode->key = k;
	newNode->total_marks=totalmarks;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

struct tree_node * insert_tree_node(int k, int totalmarks,struct tree_node *root)
{
	if (root == NULL)
	{
		root = create_tree_node(k, totalmarks);
	}
	else{
		if (root->total_marks >= totalmarks)
		{
			if (root->left != NULL)
			{
				insert_tree_node(k, totalmarks, root->left);
			}
			else{
				root->left = create_tree_node(k, totalmarks);
			}
		}
		else{
			if (root->right != NULL)
			{
				insert_tree_node(k, totalmarks, root->right);
			}
			else{
				root->right = create_tree_node(k, totalmarks);
			}
		}
	}
	return root;
}

struct tree_node * create_tree_from_sll(struct student_node  *head)
{
	struct tree_node *root = NULL;
	while (head != NULL)
	{
		root = insert_tree_node(head->key, head->total_marks,root);
		head = head->next;
	}
	return root;
}

void print_student_details_node(struct student_node *head,int no_of_subjects,int *sl_no)
{
	*sl_no += 1;
	if (head == NULL)
		return;
	printf("%d\t%15s\t", *sl_no, head->studentname);
	for (int i = 0; i < no_of_subjects; i++)
		printf("%d\t", head->marks[i]);
	printf("%d\n", head->total_marks);

}

void print_tree(struct tree_node *root,int no_of_subjects,struct student_node **Arr,int ArrLength,int *sl_no)
{
	if (root == NULL)
		return;
	if (root->right != NULL)
		print_tree(root->right,no_of_subjects,Arr,ArrLength,sl_no);
	struct student_node *head = search_by_key_and_return_pointer(Arr, root->key, ArrLength);
	print_student_details_node(head, no_of_subjects,sl_no);
	//printf("%d\t%d\t%u\n", root->key, root->total_marks,head);
	if (root->left != NULL)
		print_tree(root->left,no_of_subjects,Arr,ArrLength,sl_no);
}

int read_data_from_file(char *filename,char ***sub,struct student_node **h,int *no_of_subs,int *count_studs,struct student_node ***Arr,struct tree_node **tree)
{
	FILE *p;
	errno_t e = fopen_s(&p, filename, "r");
	if (e != 0)
	{
		return 0;
	}
	int no_of_subjects = get_no_of_subjects_from_file(p);
	if (no_of_subjects == -1)
	{
		fclose(p);
		return 1;
	}
	char **subjects = (char **)malloc(no_of_subjects*sizeof(char *));
	int success_flag=get_subject_names_array(p,subjects,no_of_subjects);
	if (success_flag == 0)
	{
		fclose(p);
		return 2;
	}
	struct student_node *head = NULL;
	head = create_students_SLL_from_file(p, no_of_subjects);
	int count_of_students = count_no_of_students(head);
	struct student_node **Arr_of_pointers = (struct student_node **)malloc(100000*sizeof(struct student_node *));
	copy_pointers_to_array(Arr_of_pointers, head);
	//print_student_node_SLL(head, no_of_subjects);
	struct tree_node *root = NULL;
	root = create_tree_from_sll(head);
	int sl_no = 0;
	//print_tree(root,no_of_subjects,Arr_of_pointers,count_of_students,&sl_no);
	//printf("\n\n");
	*sub = subjects;
	*h = head;
	*no_of_subs = no_of_subjects;
	*count_studs = count_of_students;
	*Arr = Arr_of_pointers;
	*tree = root;
	fclose(p);
	return -1;
}

int isValid_character(char c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == '.'||c=='_')
		return 1;
	return 0;
}

int is_file_name_valid(char *str)
{
	int flag;
	int dot_count = 0;
	int dotposition;
	int length = 0;
	if (str[0] >= 48 && str[0] <= 57)
	{
		printf("\nFile name should not start with number\n");
		return 0;
	}
	for (int i = 0; str[i] != '\0'; i++)
	{
		length++;
		if (str[i] == '.')
		{
			dot_count++;
			dotposition = i;
		}
		flag = isValid_character(str[i]);
		if (flag == 0)
		{
			printf("Invalid Character exists, Special symbols not allowed\n");
			return 0;
		}
	}
	if (dot_count != 1)
	{
		printf("Maybe dot not exist or more dots exist\n");
		return 0;
	}
	if (dotposition != length - 4)
	{
		printf("Not Valid format\n");
		return 0;
	}
	if (str[dotposition + 1] != 't')
	{
		printf("Not Valid format\n");
		return 0;
	}
	if (str[dotposition + 2] != 'x')
	{
		printf("Not Valid format\n");
		return 0;
	}
	if (str[dotposition + 3] != 't')
	{
		printf("Not Valid format\n");
		return 0;
	}
	return 1;
}

int check_if_file_exist(char *filename)
{
	FILE *p;
	errno_t e = fopen_s(&p, filename, "r");
	if (e != 0)
	{
		printf("File doest not exist \n Make sure file should be available in specified folder\n");
		return 0;
	}
	return 1;
}

char * getFilename()
{
	char file_name[200];
	int flag = 0;
	while (!flag)
	{
		printf("\n\nEnter the Filename, must end with .txt\nShould be available in projectname/projectname folder\n");
		gets_s(file_name);
		system("CLS");
		flag = is_file_name_valid(file_name);
		if (flag == 1)
		{
			flag = check_if_file_exist(file_name);
		}
	}
	int len = strlen(file_name);
	char *str = (char *)malloc((len + 2)*sizeof(char));
	int i;
	for (i = 0; file_name[i] != '\0'; i++)
	{
		str[i] = file_name[i];
	}
	str[i] = '\0';
	return str;
}

void print_Menu()
{
	printf("\n\n\n\n\t\t============== MENU ============\n\n\n");
	printf("\t\t1. View List of Students and Marks\n");
	printf("\t\t2. View Student Marks\n");
	printf("\t\t3.View Particular Subject Marks of All Students\n");
	printf("\t\t4.Maximum marks a Student Got in All Subjects\n");
	printf("\t\t5.Average Marks of Students\n");
	printf("\t\t6.View Particular Subject Marks of a Student\n");
	printf("\t\t7.Add a Student and Marks\n");
	printf("\t\t8.Change Student Name\n");
	printf("\t\t9.Change marks of a Student\n");
	printf("\t\t10.Delete a Student\n");
	printf("\t\t11.Display Student whose data is Missing\n");
	printf("\t\t12.Show LeaderBoard of Student\n");
	printf("\t\t13.Perform Queries Based on Subject marks and Total Score\n");
	printf("\t\t14.Exit");
	printf("\n\t\tEnter your option\n\t\t");
}

int get_Input()
{
	int n=0;
	int NotValidInput = 1;
	while (NotValidInput)
	{
		print_Menu();
		scanf_s("%d", &n);
		if (n >= 1 && n <= 14)
			return n;
		printf("\t\tEnter Valid input\n");
		getchar();
		getchar();
		system("CLS");
	}
	return 0;
}

int View_Total_list_of_students(struct student_node *head, char **subjects, int no_of_subjects)
{
	system("CLS");
	printf("Sl.No\t       Name    \t");
	for (int i = 0; i < no_of_subjects; i++)
		printf("  %3s  ", subjects[i]);
	printf("Total\n");
	print_student_node_SLL(head,no_of_subjects);
	printf("\n\n");
	printf("-1 in marks and noname in names indicates data not available\n");
	printf("Enter \n1 To goto mainmenu\nOther to exit");
	int n;
	scanf_s("%d", &n);
	return n;
}

void print_node_in_student_format(struct student_node *node,char **subjects,int no_of_subjects)
{
	printf("\n");
	printf("Name   :%s\n", node->studentname);
	printf("Subject wise marks\n\n");
	for (int i = 0; i < no_of_subjects; i++)
	{
		printf("%15s\t%d\n", subjects[i], node->marks[i]);
	}
	double average = (node->total_marks) / no_of_subjects;
	printf("\nTotal=%d\tAverage=%3f\n\n", node->total_marks, average);
}



int View_Student_Marks(struct student_node *head,struct student_node **Arr, char **subjects, int no_of_subjects,int count)
{
	system("CLS");
	int flag = 0;
	struct student_node *node;
	printf("Enter Student Name\n CaseSensitive\n");
	char name[100];
	gets_s(name);
	gets_s(name);
	while (head != NULL)
	{
		int k = strcmp(name, head->studentname);
		if (k == 0)
		{
			//printf("%d\n%d\n", count,head->key);
			node = search_by_key_and_return_pointer(Arr, head->key, count);
			//printf("%u\n%s\n", node,node->studentname);
			print_node_in_student_format(node, subjects, no_of_subjects);
			flag = 1;
		}
		head = head->next;
	}
	if (flag != 1)
	{
		printf("No student exist with that name\n");
	}
	printf("\nEnter 1 To return mainmenu\n Other to exit\n");
	int n;
	scanf_s("%d", &n);
	return n;
}

int search_subject_in_subject_list(char **subjects, char *subject,int no_of_subs)
{
	for (int i = 0; i < no_of_subs; i++)
	{
		int k = strcmp(subjects[i], subject);
		if (k == 0)
			return i;
	}
	return -1;
}


int view_particular_subject_marks_of_students(struct student_node *head, char **subjects, int no_of_subjects)
{
	system("CLS");
	printf("\n\nSubject Names\n===============\n");
	for (int i = 0; i < no_of_subjects; i++)
		printf("%d\t%s\n", i+1,subjects[i]);
	/*char subject[100];
	gets_s(subject);
	gets_s(subject);
	int k = search_subject_in_subject_list(subjects, subject, no_of_subjects);*/
	int k;
	scanf_s("%d", &k);
	if (k<1||k>no_of_subjects)
	{
		printf("InValid Subject number\n");
	}
	else{
		system("CLS");
		printf("\tName\t%s\n\n",subjects[k-1]);
		while (head != NULL)
		{
			printf("%15s\t%d\n", head->studentname, head->marks[k-1]);
			head = head->next;
		}
	}
	printf("\n\nEnter 1 to return to main menu\nOther number to exit\n");
	scanf_s("%d", &k);
	return k;
}

int view_average_marks_of_all_students(struct student_node *head, int no_of_students)
{
	system("CLS");
	printf("\tName\t\tAverage\n\n");
	double average;
	while (head != NULL)
	{
		average = ((head->total_marks) / no_of_students);
		printf("%15s\t\t%3f\n", head->studentname,average);
		head = head->next;
	}
	printf("\n Average 0 or NONAME indicates no data available to the student");
	printf("\n\n");
	printf("Enter 1 to return to main menu\nOther number to exit\n");
	int n;
	scanf_s("%d", &n);
	return n;
}

int view_particular_subject_marks_of_one_student(struct student_node *head, char **subjects, int no_of_students)
{
	system("CLS");
	printf("Subject Names\n=================\n\n");
	for (int i = 0; i < no_of_students; i++)
		printf("%d\t%s\n",i+1, subjects[i]);
	printf("\nEnter subject Number\n");
	int k;
	int flag = 1;
	scanf_s("%d", &k);
	if (k<0 || k>no_of_students)
	{
		printf("Invalid Subject Number\n");
	}
	else{
		printf("Enter the Name of the Student\n");
		char name[100];
		gets_s(name);
		gets_s(name);
		system("CLS");
		printf("\n\n");
		while (head != NULL)
		{
			int c = strcmp(name, head->studentname);
			if (c == 0)
			{
				flag = 0;
				printf("Name  :  %s\n", head->studentname);
				printf("%s marks  :  %d\n\n", subjects[k - 1], head->marks[k - 1]);
			}
			head = head->next;
		}
	}
	if (flag == 1)
	{
		printf("\nNo Student available with the given name\nName should be considered case sensitive\n");
	}
	printf("\n\n");
	printf("Enter 1 to return to main menu\nOther number to exit\n");
	int n;
	scanf_s("%d", &n);
	return n;
}


int check_given_details_are_valid(int *marks, int no_of_subjects, char *name)
{
	for (int i = 0; name[i] != '\0'; i++)
	{
		if (!((name[i] >= 65 && name[i] <= 90) || (name[i] >= 97 && name[i] <= 122)))
			return 1;
	}
	for (int i = 0; i < no_of_subjects; i++)
	{
		if (!(marks[i] >= -1 && marks[i] <= 100))
			return 2;
	}
	return 0;
}

struct student_node * add_node_in_last(struct student_node **head, char *name, int *marks, int total,int count,int no_of_subjects)
{
	struct student_node *newNode = (struct student_node *)malloc(sizeof(struct student_node));
	newNode->key = count + 1;
	strcpy_s(newNode->studentname, name);
	newNode->total_marks = total;
	newNode->marks = marks;
	newNode->next = NULL;
	struct student_node *temp_head = *head;
	while (temp_head->next != NULL)
		temp_head = temp_head->next;
	temp_head->next = newNode;
	return newNode;
}

int add_new_student(struct student_node **head, struct student_node ***Arr, int *count, char **subjects, int no_of_subjects, struct tree_node **root)
{
	struct student_node  **temp_Arr=*Arr;
	int temp_count;
	struct tree_node *temp_root;
	system("CLS");
	printf("Enter the name of the student\n");
	char name[100];
	gets_s(name);
	gets_s(name);
	int *marks_list = (int *)malloc((no_of_subjects + 2)*sizeof(int));
	int total = 0;
	for (int i = 0; i < no_of_subjects; i++)
	{
		printf("Enter marks for %s\n",subjects[i]);
		scanf_s("%d", &marks_list[i]);
		total = total + marks_list[i];
	}
	int k = check_given_details_are_valid(marks_list, no_of_subjects, name);
	system("CLS");
	if (k == 0)
	{
		struct student_node *node = add_node_in_last(head, name, marks_list, total, *count, no_of_subjects);
		//printf("count=%d\n", *count);
		temp_Arr[*count] = node;
		node = temp_Arr[*count];
		//printf("%s", node->studentname);
		*count += 1;
		*root = insert_tree_node(*count, total, *root);
		*Arr = temp_Arr;
		printf("Data Entered SuccessFully\n");
	}
	else if (k == 1)
	{
		printf("Name is Invalid\nOnly Alphabets Allowed\n ");
	}
	else if (k == 2)
	{
		printf("Marks are Not Valid\n Marks should be in the range 0 and 100\nEnter -1 if data not available\n");
	}
	printf("\n\n");
	printf("Enter 1 to return to main menu\nOther number to exit\n");
	int n;
	scanf_s("%d", &n);
	return n;
}

int check_if_given_key_matched(int key, int *keys_array, int key_count)
{
	for (int i = 0; i < key_count; i++)
	{
		if (key == keys_array[i])
			return 1;
	}
	return 0;
}


int change_student_name(struct student_node *head,struct student_node **Arr,int count)
{
	system("CLS");
	printf("\n\nEnter the Student Name you want to edit\n\n");
	char name[100];
	gets_s(name);
	gets_s(name);
	int keys_Array[100];
	int key_offset = 0;
	struct student_node *node;
	while (head != NULL)
	{
		int k = strcmp(name, head->studentname);
		if (k == 0)
		{
			node = head;
			keys_Array[key_offset] = head->key;
			key_offset++;
		}
		head = head->next;
	}
	if (key_offset == 1)
	{
		printf("\nEnter New Name\n");
		gets_s(name);
		//gets_s(name);
		strcpy_s(node->studentname, name);
		printf("Name changed Successfully\n");
	}
	else if (key_offset > 1)
	{
		printf("More than one name matched with following keys\n");
		for (int i = 0; i < key_offset; i++)
		{
			printf("%d\t", keys_Array[i]);
		}
		printf("\nEnter the key Value you want to edit\n");
		int key;
		scanf_s("%d", &key);
		int k = check_if_given_key_matched(key, keys_Array, key_offset);
		if (k == 1)
		{
			node = search_by_key_and_return_pointer(Arr, key, count);
			printf("Enter New Name\n");
			gets_s(name);
			gets_s(name);
			strcpy_s(node->studentname, name);
			printf("Name changed Successfully\n");
		}
		else{
			printf("\nInvalid Key\n");
		}
	}
	else{
		printf("\nNo Name matched with given name\n");
	}
	printf("\n\n");
	printf("Enter 1 to return to main menu\nOther number to exit\n");
	int n;
	scanf_s("%d", &n);
	return n;
}

char * convert_no_of_subjects_to_string(int n)
{
	char *str = (char *)malloc(3*sizeof(char));
	while (n > 0)
	{
		char c = (char)((n % 10) + 48);
		n = n / 10;
		if (n > 0)
		{
			str[1] = c;
			str[0] = (char)(n + 48);
			str[2] = '\0';
		}
		else{
			str[0] = c;
			str[1] = '\0';
		}
	}
	return str;
}

char * convert_number_to_string(int n)
{
	char *str = (char *)malloc(5 * sizeof(char));
	int i = 0;
	if (n<0)
	{
		str[i] = '-';
		i++;
	}
	n = abs(n);
	while (n > 0)
	{
		str[i] = (char)((n % 10) + 48);
		i++;
		n = n / 10;
	}
	str[i] = '\0';
	_strrev(str);
	return str;
}

char * convert_marks_to_string(int *marks, int no_of_subjects)
{
	char *return_string = (char *)malloc(200*sizeof(char));
	int k = 0;
	int offset = 0;
	for (int i = 0; i < no_of_subjects; i++)
	{
		char *s = convert_number_to_string(marks[i]);
		for (k = 0; s[k] != '\0'; k++)
		{
			return_string[offset] = s[k];
			offset++;
		}
		return_string[offset] = ',';
		offset++;
	}
	return_string[offset - 1] = '\0';
	return return_string;
}


int write_data_to_file(struct student_node *head, char **Subjects, int no_of_subjects, char *filename)
{
	_fcloseall();
	FILE *p;
	printf("%s\n", filename);
	errno_t e = fopen_s(&p, filename, "w");
	if (e != 0)
		return 0;
	char *s = convert_no_of_subjects_to_string(no_of_subjects);
	fputs(s,p);
	fputc('\n', p);
	for (int i = 0; i < no_of_subjects; i++)
	{
		fputs(Subjects[i], p);
		if (i != no_of_subjects - 1)
			fputc(',', p);
	}
	fputc('\n', p);
	while (head != NULL)
	{
		fputs(head->studentname, p);
		fputc('\n', p);
		char *str = convert_marks_to_string(head->marks, no_of_subjects);
		fputs(str,p);
		if (head->next != NULL)
			fputc('\n', p);
		head = head->next;
	}
	fclose(p);
	return 1;
}

int check_if_given_marks_are_valid(int *marks, int no_of_subjects)
{
	for (int i = 0; i < no_of_subjects; i++)
	{
		if (marks[i]<-1 || marks[i]>100)
			return 0;
	}
	return 1;
}

int  get_marks_from_user(char **subjects, int no_of_subjects,int **marks)
{
	int *tempmarks = (int *)malloc((no_of_subjects + 2)*sizeof(int));
	int sum = 0;
	for (int i = 0; i < no_of_subjects; i++)
	{
		printf("Enter marks for %s\n", subjects[i]);
		scanf_s("%d", &tempmarks[i]);
		sum = sum + tempmarks[i];
	}
	*marks = tempmarks;
	int k= check_if_given_marks_are_valid(tempmarks, no_of_subjects);
	if (k == 0)
		return -1;
	else
		return sum;
}

int change_student_marks(struct student_node *head, struct student_node **Arr, int count,char **subjects,int no_of_subjects)
{
	system("CLS");
	printf("\n\nEnter the Student Name you want to edit\n\n");
	char name[100];
	gets_s(name);
	gets_s(name);
	int keys_Array[100];
	int key_offset = 0;
	struct student_node *node;
	while (head != NULL)
	{
		int k = strcmp(name, head->studentname);
		if (k == 0)
		{
			node = head;
			keys_Array[key_offset] = head->key;
			key_offset++;
		}
		head = head->next;
	}
	if (key_offset == 1)
	{
		int *marks;
		int k = get_marks_from_user(subjects, no_of_subjects,&marks);
		if (k == -1)
		{
			printf("Invalid marks Try Again!!\n");
		}
		else{
			node->marks = marks;
			node->total_marks = k;
			printf("\nMarks Updated Successfully");
		}
	}
	else if (key_offset > 1)
	{
		printf("More than one name matched with following keys\n");
		for (int i = 0; i < key_offset; i++)
		{
			printf("%d\t", keys_Array[i]);
		}
		printf("\nEnter the key Value you want to edit\n");
		int key;
		scanf_s("%d", &key);
		int k = check_if_given_key_matched(key, keys_Array, key_offset);
		if (k == 1)
		{
			node = search_by_key_and_return_pointer(Arr, key, count);
			int *marks;
			int k = get_marks_from_user(subjects, no_of_subjects, &marks);
			if (k == -1)
			{
				printf("Invalid marks Try Again!!\n");
			}
			else{
				node->marks = marks;
				node->total_marks = k;
				printf("\nMarks Updated Successfully");
			}
		}
		else{
			printf("\nInvalid Key\n");
		}
	}
	else{
		printf("\nNo Name matched with given name\n");
	}
	printf("\n\n");
	printf("Enter 1 to return to main menu\nOther number to exit\n");
	int n;
	scanf_s("%d", &n);
	return n;
}

int delete_node_from_array(struct student_node **Arr, struct student_node *node,int *count)
{
	int i = 0;
	while (Arr[i] != node)
	{
		//printf("%d\t%d\n", Arr[i]->key, node->key);
		i++;
	}
	printf("\n\n");
	while (i < (*count-1))
	{
		Arr[i] = Arr[i + 1];
		//printf("%d\t%d\n", Arr[i]->key, Arr[i + 1]->key);
		i++;
	}
	*count -= 1;
	return 1;
}

int delete_student(struct student_node **original_head, struct student_node **Arr, int *count)
{
	system("CLS");
	printf("\n\nEnter the Student Name you want to edit\n\n");
	char name[100];
	gets_s(name);
	gets_s(name);
	int keys_Array[100];
	int key_offset = 0;
	struct student_node *node;
	struct student_node *head = *original_head;
	//printf("%u\n", head);
	while (head != NULL)
	{
		int k = strcmp(name, head->studentname);
		if (k == 0)
		{
			node = head;
			keys_Array[key_offset] = head->key;
			key_offset++;
		}
		head = head->next;
	}
	if (key_offset == 1)
	{
		head = *original_head;
		if (head == node)
		{
			*original_head = head->next;
		}
		else{
			while (head->next != node)
			{
				head = head->next;
			}
			head->next = node->next;
		}
		head = head->next;
		while (head != NULL)
		{
			head->key = (head->key) - 1;
			head = head->next;
		}
		printf("Data of given student deleted Successfully");
		delete_node_from_array(Arr, node, count);
	}
	else if (key_offset > 1)
	{
		printf("More than one name matched with following keys\n");
		for (int i = 0; i < key_offset; i++)
		{
			printf("%d\t", keys_Array[i]);
		}
		printf("\nEnter the key Value you want to delete\n");
		int key;
		scanf_s("%d", &key);
		int k = check_if_given_key_matched(key, keys_Array, key_offset);
		if (k == 1)
		{
			node = search_by_key_and_return_pointer(Arr, key, *count);
			head = *original_head;
			//printf("%u\t", head);
			if (head == node)
			{
				*original_head = head->next;
			}
			else{
				while (head->next != node)
				{
					//printf("Mahndar");
					head = head->next;
				}
				head->next = node->next;
			}
			head = head->next;
			while (head != NULL)
			{
				head->key = (head->key) - 1;
				head = head->next;
			}
			printf("Data of given student deleted Successfully");
			delete_node_from_array(Arr, node, count);
		}
		else{
			printf("\nInvalid key\n");
		}
	}
	else{
		printf("\nNo Name matched with given name\n");
	}
	printf("\n\n");
	printf("Enter 1 to return to main menu\nOther number to exit\n");
	int n;
	scanf_s("%d", &n);
	return n;
}

int show_missing_data_students(struct student_node *head)
{
	system("CLS");
	int flag = 0;
	printf("\n\n");
	while (head != NULL)
	{
		if (head->total_marks == 0)
		{
			printf("%s\n\n", head->studentname);
			flag = 1;
		}
		head = head->next;
	}
	if (flag == 0)
		printf("No Students Data is Missing\n\n");
	printf("\n\n");
	printf("Enter 1 to return to main menu\nOther number to exit\n");
	int n;
	scanf_s("%d", &n);
	return n;
}

int show_leaderboard(struct student_node *head, struct student_node **Arr, char **subjects, int no_of_subjects, int count)
{
	system("CLS");
	struct tree_node *root = create_tree_from_sll(head);
	int sl = 0;
	printf("Sl.No\t       Name    \t");
	for (int i = 0; i < no_of_subjects; i++)
		printf("  %3s  ", subjects[i]);
	printf("Total\n\n");
	print_tree(root, no_of_subjects, Arr, count, &sl);
	printf("\n\n");
	printf("Enter 1 to return to main menu\nOther number to exit\n");
	int n;
	scanf_s("%d", &n);
	return n;
}

int view_maximum_marks_a_student_got_in_all_subjects(struct student_node *head, char **subjects, int no_of_subjects, struct student_node **Arr, int count)
{
	system("CLS");
	int arr[100];
	int arr_offset = 0;
	int max = 0;
	int i;
	printf("\n\n\tName\t\tMaxMarks\t\tSubjects\n\n");
	while (head != NULL)
	{
		arr_offset = 0;
		max = 0;
		for (i = 0; i < no_of_subjects; i++)
		{
			if (max < head->marks[i])
			{
				arr_offset = 0;
				max = head->marks[i];
				arr[arr_offset] = i;
				arr_offset++;
			}
			else if (max == head->marks[i])
			{
				arr[arr_offset] = i;
				arr_offset++;
			}
		}
		//printf("arroffset=%d\n", arr_offset);
		printf("%15s\t\t", head->studentname);
		printf("%d\t\t", max);
		for (int j = 0; j < arr_offset; j++)
		{
			printf("%s,", subjects[arr[j]]);
		}
		printf("\n");
		head = head->next;
	}
	printf("\n\n");
	printf("Enter 1 to return to main menu\nOther number to exit\n");
	int n;
	scanf_s("%d", &n);
	return n;
}

char * remove_spaces_from_given_query(char *str)
{
	int length = strlen(str);
	char *return_string = (char *)malloc(length*sizeof(char));
	int k = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != ' ')
		{
			return_string[k] = str[i];
			k++;
		}
	}
	return_string[k] = '\0';
	return return_string;
}

int isValidChar_for_query(char ch)
{
	if ((ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || ch == '>' || ch == '<' || ch == '=')
		return 1;
	return 0;
}

int check_if_given_query_valid(char *str)
{
	char *strtemp = remove_spaces_from_given_query(str);
	int opcount = 0;
	int opcount_flag = 0;
	int afterchar = 0;
	for (int i = 0; strtemp[i] != '\0'; i++)
	{
		int flag = isValidChar_for_query(strtemp[i]);
		if (opcount_flag == 1)
		{
			afterchar++;
		}
		if (str[i] == '<' || str[i] == '=' || str[i] == '>')
		{
			opcount_flag = 1;
			opcount++;
		}
		if (flag == 0)
			return 0;
	}
	if (opcount != 1 || afterchar <= 0)
		return 0;
	return 1;
}

int check_operation(int original_score, int given_score, char op)
{
	switch (op)
	{
	case '>':
		if (original_score > given_score)
		{
			return 1;
		}
		return 0;
	case '<':
		if (original_score < given_score)
		{
			return 1;
		}
		return 0;
	case '=':
		if (original_score == given_score)
		{
			return 1;
		}
		return 0;
	}
}

int split_query_into_tokens(char **subjects,int no_of_subjects,struct student_node *head)
{
	system("CLS");
	char subjectname[100], value[10];
	char op;
	int opflag = 0;
	int subnameoffset = 0;
	int valoffset = 0;
	char query1[200];
	int score;
	int execure_flag = 0;
	printf("Enter the Query\n\nSuppoted and sample query types\nsubject_name>100(number of int type)\nTotal>100(number of type int)\nOperators allowed :>\t<\t=\t (only)\n\n");
	gets_s(query1);
	gets_s(query1);
	char *query = remove_spaces_from_given_query(query1);
	int k = check_if_given_query_valid(query1);
	if (k == 0)
	{
		system("CLS");
		printf("\n\nInvalid Query\n Try Again!!\n");
	}
	else{
		for (int i = 0; query[i] != '\0'; i++)
		{
			if (query[i] == '>' || query[i] == '=' || query[i] == '<')
			{
				op = query[i];
				opflag = 1;
				i++;
			}
			if (opflag == 0)
			{
				subjectname[subnameoffset] = query[i];
				subnameoffset++;
			}
			else{
				value[valoffset] = query[i];
				valoffset++;
			}
		}
		subjectname[subnameoffset] = '\0';
		value[valoffset] = '\0';
		score = convert_from_string_to_int(value);
		int subject_index=-1;
		for (int i = 0; i < no_of_subjects; i++)
		{
			int r_value = strcmp(subjectname, subjects[i]);
			if (r_value == 0)
			{
				subject_index = i;
				break;
			}
		}
		if (subject_index != -1)
		{
			system("CLS");
			execure_flag = 1;
			int temp_flag = 0;
			printf("\n\n");
			while (head != NULL)
			{
				int r_value = check_operation(head->marks[subject_index], score, op);
				if (r_value == 1)
				{
					printf("%15s\t%d\n", head->studentname, head->marks[subject_index]);
					temp_flag = 1;
				}
				head = head->next;
			}
			if (temp_flag == 0)
			{
				printf("\n\nNo Student Found with Given Condition\n\n");
			}
		}
		else if (!strcmp(subjectname, "Total"))
		{
			system("CLS");
			int temp_flag = 0;
			printf("\n\n");
			while (head != NULL)
			{
				int r_value = check_operation(head->total_marks, score, op);
				if (r_value == 1)
				{
					printf("%15s\t%d\n", head->studentname, head->total_marks);
					temp_flag = 1;
				}
				head = head->next;
			}
			if (temp_flag == 0)
			{
				printf("\n\nNo Students Found With Given Condition\n");
			}
		}
		else{
			printf("\n\nInvalid Subject or Value\n");
		}
	}
	printf("\n\n");
	printf("Enter 1 to return to main menu\nOther number to exit\n");
	int n;
	scanf_s("%d", &n);
	return n;
}

int process_data_from_file_and_mainfuction()
{
	char **subjects=NULL;
	struct student_node *head=NULL;
	int no_of_subjects=0;
	int count_of_students=0;
	struct student_node **Arr_Pointers=NULL;
	struct tree_node *total_tree=NULL;
	char *file_name=getFilename();
	int k;
	//printf("This is executed");
	int return_value=read_data_from_file(file_name,&subjects, &head, &no_of_subjects, &count_of_students, &Arr_Pointers, &total_tree);
	//printf("This is executed");
	if (return_value == -1)
	{
		printf("File Read Successfully\nClick any key to view Menu\n");
		getchar();
		int flag = 1;
		while (flag)
		{
			system("CLS");
			int n = get_Input();
			switch (n)
			{
			case 1:k= View_Total_list_of_students(head, subjects, no_of_subjects);
				if (k != 1)
				{
					flag = 0;
				}
				break;
			case 2:k = k=View_Student_Marks(head,Arr_Pointers, subjects, no_of_subjects,count_of_students);
				if (k != 1)
				{
					flag = 0;
				}
				break;
			case 3:k = view_particular_subject_marks_of_students(head, subjects, no_of_subjects);
				if (k != 1)
				{
					flag = 0;
				}
				break;
			case 4:k = view_maximum_marks_a_student_got_in_all_subjects(head, subjects, no_of_subjects, Arr_Pointers, count_of_students);
				if (k != 1)
				{
					flag = 0;
				}
				break;
			case 5:k = view_average_marks_of_all_students(head, no_of_subjects);
				if (k != 1)
				{
					flag = 0;
				}
				break;
			case 6:k = view_particular_subject_marks_of_one_student(head, subjects, no_of_subjects);
				if (k != 1)
				{
					flag = 0;
				}
				break;
			case 7:k = add_new_student(&head,&Arr_Pointers,&count_of_students,subjects,no_of_subjects,&total_tree);
				if (k != 1)
				{
					flag = 0;
				}
				break;
			case 8:k = change_student_name(head,Arr_Pointers,count_of_students);
				if (k != 1)
				{
					flag = 0;
				}
				break;
			case 9:k = change_student_marks(head, Arr_Pointers, count_of_students, subjects, no_of_subjects);
				if (k != 1)
				{
					flag = 0;
				}
				break;
			case 10:k = delete_student(&head,Arr_Pointers,&count_of_students);
				if (k != 1)
				{
					flag = 0;
				}
				break;
			case 11:k = show_missing_data_students(head);
				if (k != 1)
				{
					flag = 0;
				}
				break;
			case 12:k = show_leaderboard(head, Arr_Pointers, subjects, no_of_subjects, count_of_students);
				if (k != 1)
				{
					flag = 0;
				}
				break;
			case 13:k = split_query_into_tokens(subjects, no_of_subjects, head);
				if (k != 1)
				{
					flag = 0;
				}
				break;
			case 14:flag = 0; break;
			}
		}
	}
	else if (return_value == 1)
	{
		printf("Subjects line is not valid\nGive Correct File\nProgram exiting");
		getchar();
		return 0;
	}
	else if (return_value == 2)
	{
		printf("Some error in subjects line\nGive Correct File\nProgram exiting");
		getchar();
		return 0;
	}
	system("CLS");
	printf("Writing data to file....");
	int q=write_data_to_file(head, subjects, no_of_subjects, file_name);
	if (q == 0)
		printf("Some error occured opening the file\nData not copied to file");
	else
		printf("Data copied to the file successfully\n\nClick Any Key To Close");
	_fcloseall();
	getchar();
	return 0;
}


int main()
{
	process_data_from_file_and_mainfuction();
	//int k = check_if_string_no_is_valid_or_not("23\n21\n");
	//printf("%d", k);
	//int k=check_if_subjects_string_isValid("Maths,Physics,,Chemistry,Aptitude,Combat", 5);
	//printf("%d", k);
	//int *marks=NULL;
	//int k = modify_marks_Array_to_original_marks("100,100,30\n",marks,6);
	//printf("%d", k);
	//int k = is_file_name_valid("filename.txt");
	//printf("%d", k);
	//char *str = getFilename();
	//printf("%s", str);
	//int k=check_if_given_query_valid("Mahendar>1");
	//printf("%d", k);
	//split_query_into_tokens("Mahendar>100");
	getchar();
	return 0;
}