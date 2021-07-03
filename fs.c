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

    init_inodes();

    return 0;
}

void init_inodes(void)
{
    int i;
    int buffer_offset = 0;
    int current_block = INODE_BLOCK;
    int inode_size = INODE_SIZE_BYTES;
    unsigned char *buffer_address = (unsigned char *)buffer;

    inode_t inode;

    inode.used = 0;
    inode.is_dir = 0;
    inode.links = 0;
    inode.file_size = 0;
    inode.dbl1 = 0;
    inode.dbl2 = 0;
    inode.dbl3 = 0;
    inode.dbl4 = 0;
    inode.dbl5 = 0;
    inode.dbl6 = 0;
    inode.dbl7 = 0;
    inode.dbl8 = 0;
    inode.dbl9 = 0;
    inode.dbl10 = 0;
    inode.ibl1 = 0;
    inode.ibl2 = 0;

    for (i = 0; i < INODES; i++)
    {
        inode.index = i;
        block_read(current_block, buffer);
        bcopy((unsigned char *)&inode, buffer_address, inode_size);
        buffer_offset += inode_size;

        if (buffer_offset >= sizeof(buffer))
        {
            block_write(current_block, buffer);
            buffer_offset = 0;
            current_block += 1;
        }
    }
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
