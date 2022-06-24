#include <stdio.h>
#include <mntent.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char desired_path[] = "sys/fs/cgroup/unified";
    FILE *mount_info;
    struct mntent *me;
    mount_info = setmntent("/proc/mounts", "r");
    int best_fit_length = 0;
    char *options = 0;
    while (me = getmntent(mount_info)) {
        if(!strcmp(desired_path, me->mnt_dir))
        {
            printf("found ='%s'\n", me->mnt_dir);
            free(options);
            options = malloc(strlen(me->mnt_opts) + 1);
            if (options)
            {
                strcpy(options,me->mnt_opts);
            }
            else
            {
                printf("Failed to allocate memory");
            }
            //break;
        }
        else
        {
            if(strstr(desired_path, me->mnt_dir))
            {
                printf("it is part of ='%s'\n", me->mnt_dir);
                if (best_fit_length < strlen(me->mnt_dir))
                {
                    best_fit_length = strlen(me->mnt_dir);
                    free(options);
                    options = malloc(strlen(me->mnt_opts) + 1);
                    if (options)
                    {
                        strcpy(options,me->mnt_opts);
                    }
                    else
                    {
                        printf("Failed to allocate memory");
                    }
                }
            }
        }
    }
    printf("Longest fit = %d\n", best_fit_length);
    printf("options are %s\n", options);
    free(options);
}

