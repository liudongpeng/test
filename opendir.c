#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>


int main()
{
	DIR* pDir = opendir(".");
	if(!pDir)
	{
		return -1;
	}
	
	struct stat st;
	memset(&st, 0, sizeof(st));

	struct passwd pd;
	memset(&pd, 0, sizeof(pd));
	struct passwd *pwd = &pd;

	struct group gp;
	memset(&gp, 0, sizeof(gp));
	struct group *pgp;

	struct tm time;
	memset(&time, 0, sizeof(time));
	struct tm *ptime = &time;

	int count = 0;

	struct dirent *ptr = NULL;
	while((ptr = readdir(pDir)) != NULL)
	{
		if((stat(ptr->d_name, &st)) == -1)
		{
			return -1;
		}

		if(S_ISREG(st.st_mode))
		{
			printf("-");
		}
		if(S_ISDIR(st.st_mode))
		{
			printf("d");
		}
		if(S_ISCHR(st.st_mode))
		{
			printf("c");
		}
		if(S_ISBLK(st.st_mode))
		{
			printf("b");
		}

		if(S_IRUSR & st.st_mode)
		{
			printf("r");
		}
		else
		{
			printf("-");
		}
		if(S_IWUSR & st.st_mode)
		{
			printf("w");
		}
		else
		{
			printf("-");
		}
		if(S_IXUSR & st.st_mode)
		{
			printf("x");
		}
		else
		{
			printf("-");
		}

		if(S_IRGRP & st.st_mode)
		{
			printf("r");
		}
		else
		{
			printf("-");
		}
		if(S_IWGRP & st.st_mode)
		{
			printf("w");
		}
		else
		{
			printf("-");
		}
		if(S_IXGRP & st.st_mode)
		{
			printf("x");
		}
		else
		{
			printf("-");
		}

		if(S_IROTH & st.st_mode)
		{
			printf("r");
		}
		else
		{
			printf("-");
		}
		if(S_IWOTH & st.st_mode)
		{
			printf("w");
		}
		else
		{
			printf("-");
		}
		if(S_IXOTH & st.st_mode)
		{
			printf("x ");
		}
		else
		{
			printf("- ");
		}

		printf("%lu ", st.st_nlink);

		pwd = getpwuid(st.st_uid);
		printf("%s ", pwd->pw_name);

		pgp = getgrgid(st.st_gid);
		printf("%s ", pgp->gr_name);

		printf("%6lu ", st.st_size);

		localtime_r(&st.st_mtime, ptime);
		printf("%d月  %d %d:", ptime->tm_mon + 1, ptime->tm_mday,
			   	ptime->tm_hour);

		if(ptime->tm_min >= 0 && ptime->tm_min <= 9)
		{
			printf("0%d ", ptime->tm_min);
		}
		else
		{
			printf("%d ", ptime->tm_min);
		}

		if(S_ISDIR(st.st_mode))
		{
				printf("\033[34m%s\033[0m\n", ptr->d_name);
		}

		if(S_ISREG(st.st_mode))
		{
			if((S_IXUSR & st.st_mode) || (S_IXGRP & st.st_mode) 
				|| (S_IXOTH & st.st_mode))
			{
				printf("\033[32m%s\033[0m\n", ptr->d_name);
			}
			else
			{
				printf("%s\n", ptr->d_name);
			}

		}
		
		count++;
	}


	printf("total %d\n", count);


	closedir(pDir);
	return 0;
}
