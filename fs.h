#ifndef FS_INCLUDED
#define FS_INCLUDED

#define FS_SIZE 2048
#define MAGIC_NUMBER 0x003E2255
#define INODES 320
#define INODE_SIZE_BYTES 32
#define INODE_BLOCK 1
#define MAP_BLOCK ((INODES * INODE_SIZE_BYTES) / BLOCK_SIZE)
#define DATA_BLOCK (MAP_BLOCK + 1)

void fs_init(void);
int fs_mkfs(void);
int fs_open(char *fileName, int flags);
int fs_close(int fd);
int fs_read(int fd, char *buf, int count);
int fs_write(int fd, char *buf, int count);
int fs_lseek(int fd, int offset);
int fs_mkdir(char *fileName);
int fs_rmdir(char *fileName);
int fs_cd(char *dirName);
int fs_link(char *old_fileName, char *new_fileName);
int fs_unlink(char *fileName);
int fs_stat(char *fileName, fileStat *buf);
void int2disk(int integer, int position, char *buffer);
int disk2int(char *buffer, int position);
void inode2disk(char *buffer, short inode_idx);
void buffer_alloc(void);

typedef struct inode //32 bytes
{
    char used;       // 1B - usado ou não
    char is_dir;     // 2B - se é diretório ou não
    short index;     // 4B - índice do inode
    short links;     // 6B - quantidade de links
    short file_size; // 8B - tamanho do arquivo
    // blocos diretos
    short dbl1;  // 10B
    short dbl2;  // 12B
    short dbl3;  // 14B
    short dbl4;  // 16B
    short dbl5;  // 18B
    short dbl6;  // 20B
    short dbl7;  // 22B
    short dbl8;  // 24B
    short dbl9;  // 26B
    short dbl10; // 28B
    // blocos indiretos
    short ibl1; // 30B
    short ibl2; // 32B

} inode_t;

#define MAX_FILE_NAME 32
#define MAX_PATH_NAME 256 // This is the maximum supported "full" path len, eg: /foo/bar/test.txt, rather than the maximum individual filename len.

#endif
