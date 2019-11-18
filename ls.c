#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

/*
  struct dirent {
      ino_t          d_ino;        inode 番号 
      off_t          d_off;        オフセットではない; 注意を参照 
      unsigned short d_reclen;     このレコードの長さ 
      unsigned char  d_type;       ファイル種別。全ファイルシステムでサポートされているわけではない 
      char           d_name[256];  ファイル名 
  };
*/


int main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *ent;
    char dirname[256];

    // 引数がない場合は強制的にカレントディレクトリを ls するようにする
    if (argc == 1) {
        strcpy(dirname, ".");
    } else {
        strcpy(dirname, argv[1]);
    }

    dir = opendir(dirname);
    if (dir == NULL) {
        fprintf(stderr, "unable to opendir %s\n", dirname);
        return 1;
    }

    while ((ent = readdir(dir)) != NULL) {
        // .から始まる隠しファイルを消す
        if (ent->d_name[0] == '.') {
            continue;
        }

        printf("%s  ", ent->d_name);
    }
    printf("\n");

    closedir(dir);
    return 0;
}
