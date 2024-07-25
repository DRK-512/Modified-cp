#include "functions.h"

// Here we init the values, basically I take in the inputs, and the return values I care about are: 
// nCopies = number of copies to make a files
// verbose = show the progress of copying these files
// srcPath = the name of the file you want to duplicate
// destPath = where the file will end up, the default is ./
int init_values(int argc, char** argv, int* nCopies, int* verbose, char** srcPath, char** destPath) {
	int dispHelp=0; 

	for (int i = 1; i < argc; i++) {
		if ((strcmp(argv[i], "-n") == 0) && (i + 1 < argc)) {
			*nCopies = atoi(argv[i + 1]);
			i++;
		} else if ((strcmp(argv[i], "-v") == 0) || (strcmp(argv[i], "--verbose") == 0)) {
			*verbose=1;
		} else if (((strcmp(argv[i], "-s") == 0) || (strcmp(argv[i], "--source") == 0)) && (i + 1 < argc)) {
			*srcPath = malloc(strlen(argv[i+1]+1));
			strcpy(*srcPath, argv[i+1]);
			// if it starts with ./ I dont care
			if (*srcPath[0] == '.' && *srcPath[1] == '/') {
				memmove(srcPath, srcPath + 2, strlen(*srcPath) - 1);
			}
		} else if (((strcmp(argv[i], "-d") == 0) || (strcmp(argv[i], "--destination") == 0)) && (i + 1 < argc)) {
			if(argv[i+1][strlen(argv[i+1]) - 1] == '/') {
				*destPath = malloc(strlen(argv[i+1]+1));
				strcpy(*destPath, argv[i+1]);	
			} else {
				*destPath = malloc(strlen(argv[i+1]) + 2);
				strcpy(*destPath, argv[i+1]);
				destPath[strlen(*destPath)] = "/";
				*destPath[strlen(*destPath) + 1] = '\0'; 
			}
		} else if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0)) {
			dispHelp++; 
		}
	}

	if (*srcPath == NULL || dispHelp) {
		fprintf(stderr, "Usage: %s [-n num_copies] [-s] <source_file> <destination_file>\n", argv[0]);
		return EXIT_FAILURE;
	}
	if (*destPath==NULL) {
		*destPath = malloc(strlen("./\0"));
		strcpy(*destPath, "./\0");
	}
	return EXIT_SUCCESS;
}

// check if the dest dir exists
int dir_exists(const char *path) {
	struct stat info;

	if (stat(path, &info) != 0) {
		printf("ERROR: %s does not exist", path); 
		return EXIT_FAILURE;
	} else if (info.st_mode & S_IFDIR) {
		return EXIT_SUCCESS;
	} else {
		printf("ERROR: %s does not exist", path); 
		return EXIT_FAILURE;
	}
}

// this will take srcPath and split from the first .
// so if srcPath = file.old.txt then pre = file and post = .old.txt
void split_file(char* srcPath, char** pre_ext, char** post_ext) {
	*post_ext = strchr(srcPath, '.');
	if(*post_ext==NULL) {
		*post_ext = "\0";  
	}

	size_t pre_len = strlen(srcPath) - strlen(*post_ext); 

	*pre_ext = malloc(pre_len + 1);

	strncpy(*pre_ext, srcPath, pre_len);
	return; 
}

// gets num of digits, so 1235 would return 4
int get_num_digits(int num) {
	int count; 
	if(num==0) {
		return 1; 
	}
	while(num!=0) {
		num /= 10;
		count++;
	}
	return count; 
}

// copies a file a number of times with a progress as well
void copyFile(const char *old_file, const char *new_file) {
	FILE *srcFile = fopen(old_file, "rb");
	if (srcFile == NULL) {
		perror("Error opening source file");
		exit(EXIT_FAILURE);
	}

	// figure out the size of the srcFile
	fseek(srcFile, 0, SEEK_END);
	long fileSize = ftell(srcFile);
	fseek(srcFile, 0, SEEK_SET);

	// create buffer to hold content of the file
	char *buffer = malloc(fileSize);
	if (buffer == NULL) {
		perror("Error allocating memory");
		fclose(srcFile);
		exit(EXIT_FAILURE);
	}
	// Read the entire file into the buffer
	fread(buffer, 1, fileSize, srcFile);
	fclose(srcFile);

	FILE *destFile = fopen(new_file, "wb");

	if (destFile == NULL) {
		perror("Error opening destination file");
		free(buffer);
		exit(EXIT_FAILURE);
	}

	// now write the buffer to the destination file
	fwrite(buffer, 1, fileSize, destFile);

	free(buffer);   
	fclose(destFile);
}
