#include <stdlib.h> //malloc
#include <stdio.h>  //printf

#include "util.h"
#include "common.h"
#include "block.h"
#include "fs.h"

#ifdef FAKE
#include <stdio.h>
#define ERROR_MSG(m) printf m;
#else
#define ERROR_MSG(m)
#endif

char *buffer;

void fs_init(void)
{
    int magic_num_disk = 0;

    block_init();
    /*Verificar se o superblock contém o número mágico
    Se tiver: disco é formatado
    Senão: disco não é reconhecido como formatado, chama fs_mkfs para formatar*/

    buffer_alloc();
    block_read(SUPERBLOCK, buffer);
    magic_num_disk = disk2int(buffer, BLOCK_SIZE - 4);
    if (magic_num_disk != MAGIC_NUMBER)
    {
        printf("Disco não está formatado\n");
        printf("Formatando...\n");
        fs_mkfs(); //Não sei pq, mas tenho que chamar duas vezes a função pra escrever de fato no disco
        fs_mkfs();
    }
    else
    {
        printf("Disco já está no formato\n");
    }
}

int fs_mkfs(void)
{
    int volume_size = FS_SIZE;
    int data_blocks = (volume_size - INODES - 2); // Tamanho do volume menos os inodes, superblock e mapa de bits
    /*
    Chama block_write para escrever no primeiro bloco (superblock)
    Escreve no superblock o número mágico definido em fs.h

    - Nº de inodes
    - Nº blocos de dados
    - indice inodes
    - indice blocos de dados
    - 
    */

    int2disk(volume_size, 0, buffer);
    int2disk(INODES, 4, buffer);
    int2disk(data_blocks, 8, buffer);
    int2disk(INODE_BLOCK, 12, buffer);
    int2disk(MAP_BLOCK, 16, buffer);
    int2disk(DATA_BLOCK, 20, buffer);
    int2disk(BLOCK_SIZE, 24, buffer);
    int2disk(MAGIC_NUMBER, BLOCK_SIZE - 4, buffer);

    block_write(SUPERBLOCK, buffer);
    block_read(INODE_BLOCK, buffer);

    //block_read(INODE_BLOCK, buffer);
    inode_t inode;
    inode.used = 1;
    inode.is_dir = 1;
    inode.index = 1;
    inode.links = 1;
    inode.file_size = 1;
    inode.dbl1 = 1;
    inode.dbl2 = 1;
    inode.dbl3 = 1;
    inode.dbl4 = 1;
    inode.dbl5 = 1;
    inode.dbl6 = 1;
    inode.dbl7 = 1;
    inode.dbl8 = 1;
    inode.dbl9 = 1;
    inode.dbl10 = 1;
    inode.ibl1 = 1;
    inode.ibl2 = 2;

    printf("SIZE OF INODE = %d\n", (int)sizeof(inode));
    bcopy((unsigned char *)&inode, (unsigned char *)buffer, sizeof(inode));
    block_write(INODE_BLOCK, buffer);

    return 0;
}

void int2disk(int integer, int position, char *buffer)
{
    int i;
    int bits_offset = 24;
    for (i = 0; i < 4; i++)
    {
        buffer[position + i] = (integer >> bits_offset);
        bits_offset -= 8;
    }
    printf("[%d] Passado ao buffer com sucesso\n", integer);
}

int disk2int(char *buffer, int position)
{
    int i, integer = 0, bits_offset = 24;
    for (i = 0; i < 4; i++)
    {
        integer |= buffer[position + i] << bits_offset;
        bits_offset -= 8;
    }
    return integer;
}

void inode2disk(char *buffer, short inode_idx)
{
}

void buffer_alloc(void)
{
    if (!buffer)
    {
        buffer = (char *)malloc(BLOCK_SIZE * sizeof(char));
        if (!buffer)
        {
            printf("Erro ao alocar buffer\n");
            exit(EXIT_FAILURE);
        }
    }
}

int fs_open(char *fileName, int flags)
{
    return -1;
}

int fs_close(int fd)
{
    return -1;
}

int fs_read(int fd, char *buf, int count)
{
    return -1;
}

int fs_write(int fd, char *buf, int count)
{
    return -1;
}

int fs_lseek(int fd, int offset)
{
    return -1;
}

int fs_mkdir(char *fileName)
{
    return -1;
}

int fs_rmdir(char *fileName)
{
    return -1;
}

int fs_cd(char *dirName)
{
    return -1;
}

int fs_link(char *old_fileName, char *new_fileName)
{
    return -1;
}

int fs_unlink(char *fileName)
{
    return -1;
}

int fs_stat(char *fileName, fileStat *buf)
{
    return -1;
}
