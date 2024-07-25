#include "functions.h"

int main(int argc, char *argv[]) {
	
	int nCopies=1, verbose=0;
	char *srcPath=NULL, *destPath=NULL, *pre_ext=NULL, *post_ext=NULL;

	if ((init_values(argc, argv, &nCopies, &verbose, &srcPath, &destPath)) || (dir_exists(destPath))) {
		return EXIT_FAILURE;
	} 
	printf("Now copying %s to %s %d time(s)\n", srcPath, destPath, nCopies); 
	
    	split_file(srcPath, &pre_ext, &post_ext); 
	
	size_t dest_path_size = strlen(destPath); 
	size_t pre_ext_size = strlen(pre_ext);
	size_t post_ext_size = strlen(post_ext);
    	for (int i = 1; i <= nCopies; i++) {
	
		int num_i = get_num_digits(i);
		char* new_file = malloc(dest_path_size + pre_ext_size + num_i + post_ext_size + 1); 
		char* tmpStr = malloc(num_i+1); 
		sprintf(tmpStr, "%d", i); 

		strcat(new_file, destPath);
		strcat(new_file, pre_ext);
		strcat(new_file, tmpStr);
		strcat(new_file, post_ext);

		copyFile(srcPath, new_file);
		if (verbose) {
			printf("Created %s from %s\n", new_file, srcPath);
		}
    	}

    printf("Files copied successfully.\n");

    return EXIT_SUCCESS;
}

