#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

const char* diffname[] = {"NORMAL", "HYPER", "ANOTHER", "BEGINNER"};
const char* pacemarker[] = {"F", "F", "E", "D", "C", "B", "A", "AA", "AAA", "MAX"};
FILE *fp, *fpout, *fpdir;
char fname[15], tmpname[15] = "haha", musicid[5];
int content[10];
int diff, counter = 0;

int main(){
	printf("OverDrive's Insane IIDX Score Dump Tool\n");
	printf("Please put it inside the directory where *.sco files exist.\n");
	printf("Press any key to continue.\n");
	getchar();
	system("dir /b > dir.txt");
	fpdir = fopen("dir.txt", "r");
	fpout = fopen("Result.txt", "w");
	fprintf(fpout, "MusicID\tDifficulty\tBestScore\tRank\n");
	while(1){
		fscanf(fpdir, "%s", fname);
		if(!strcmp(tmpname, fname)){
			break;
		}
		strcpy(tmpname, fname);
		printf("File name: %s\n", fname);
		//sprintf(fname, "%s%c", "01000_2.sco", '\0');
		int length = strlen(fname);
		int flag = 0;
		char temp[4];
		sprintf(temp, "%c%c%c%c", fname[length-3], fname[length-2], fname[length-1], '\0');
		flag = strcmp("sco", temp);
		if(!flag){	
			fp = fopen(fname, "r");
			if(fname[7] == '.'){
				strncpy(musicid, fname, 5);
				printf("MusicID: %s\n", musicid);
				fprintf(fpout, "%s\t", musicid);
				diff = fname[6] - '0';
				if(diff < 4 && diff >= 0){
					printf("Difficulty: %s\n", diffname[diff]);
					fprintf(fpout, "%s\t", diffname[diff]);
				}
				else{
					printf("Difficulty Read Error.\n");
					fclose(fp);
					continue;
				}
			}
			else{
				fclose(fp);
				continue;
				//urafumen diff
			}
			//printf("File opened.\n");
			for(int i=0; i<10; i++){
				content[i] = fgetc(fp);
			}
			/*for(int i=0; i<10; i++){
				printf("%x ", content[i]);
			}
			printf("\n");*/
			int total = content[5] * 16 * 16 + content[4];
			int score = content[9] * 16 * 16 + content[8];
			printf("Your best score: %d\n", score);
			fprintf(fpout, "%d\t", score);
			int pacenum = 0;
			for(int i=8; i>=0; i--){
				double pace = total * i / 9.0;
				if(score >= ceil(pace)){
					pacenum = i;
					break;
				}
			}
			printf("Rank: %s\n\n", pacemarker[pacenum]);
			fprintf(fpout, "%s\n", pacemarker[pacenum]);
			fclose(fp);
			counter++;
		}
		if(flag){
			printf("File skipped.\n\n");
		}
	}
	fclose(fpout);
	fclose(fpdir);
	system("del dir.txt");
	printf("%d sco files detected.\n\n", counter);
	system("pause");
	return 0;
}
