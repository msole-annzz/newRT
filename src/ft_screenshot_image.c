#include "rtv1.h"
#define BMP_HEADER_SIZE 14
#define BMP_INFO_SIZE (OFFSET - BMP_HEADER_SIZE)
#define OFFSET 54
#define PLANES 1

char	*create_name_file(const char *name, const char *type)
{
	const char	*direction;
	char		*file_name;
	char		*tmp_name;
	char		*tmp;

	direction = "screen/";
	tmp = ft_strjoin(direction, "screen_");
	tmp_name = ft_strsub(name, 0, ft_strlen(name) - 3);
	file_name = ft_strjoin(tmp, tmp_name);
	free(tmp_name);
	free(tmp);
	tmp = NULL;
	tmp_name = NULL;
	tmp = file_name;
	file_name = ft_strjoin(tmp, type);
	free(tmp);
	tmp = NULL;
	return (file_name);
}

void	copy_pixel_bmp(unsigned char *image, int *color, size_t num)
{
	size_t	n;

	n = 0;
	while (n < num)
	{
		image[n * 4 + 3] = (unsigned char)(0x00);
		image[n * 4 + 2] = (unsigned char)((color[n] >> 16) & 0xFF);
		image[n * 4 + 1] = (unsigned char)((color[n] >> 8) & 0xFF);
		image[n * 4 + 0] = (unsigned char)(color[n] & 0xFF);
		n += 1;
	}
}

void	create_header_bmp(t_rtv *paint, char *bmp, int file_size)
{
	ft_memcpy(bmp, "BM", 2);
	*(unsigned int *)(bmp + 2) = file_size;
	*(unsigned int *)(bmp + 10) = OFFSET;
	*(unsigned int *)(bmp + 14) = BMP_INFO_SIZE;
	*(unsigned int *)(bmp + 18) = paint->width;
	*(unsigned int *)(bmp + 22) = -paint->height;
	*(unsigned short *)(bmp + 26) = PLANES;
	*(unsigned short *)(bmp + 28) = (short)paint->bpp;
}

void	save_bmp_file(t_rtv *paint)
{
	unsigned char	image[paint->width * paint->height * 4];
	int				fd;
	int				file_size;
	char			*bmp;
	char			*file_name;

	file_name = NULL;
	file_name = create_name_file(paint->name_file, ".bmp");
	if ((fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) > 0)
	{
		if ((bmp = malloc(OFFSET)))
		{
			ft_bzero(bmp, OFFSET);
			file_size = paint->width * paint->height * 4 + OFFSET;
			create_header_bmp(paint, bmp, file_size);
			copy_pixel_bmp(image, paint->draw, paint->width * paint->height);
			write(fd, bmp, OFFSET);
			write(fd, image, paint->width * paint->height * 4);
			free(bmp);
			close(fd);
			write(1, "Image saved\n", 12);
		}
	}
}

void	copy_pixel_ppm(unsigned char *image, int *color, size_t num)
{
	size_t	n;

	n = 0;
	while (n < num)
	{
		image[n * 3 + 0] = (unsigned char)((color[n] >> 16) & 0xFF);
		image[n * 3 + 1] = (unsigned char)((color[n] >> 8) & 0xFF);
		image[n * 3 + 2] = (unsigned char)(color[n] & 0xFF);
		n += 1;
	}
}

/*
** PPM header info, including the size of the image
** "P6 %d %d %d\n", paint->width, paint->height, 255
*/

void	create_header_ppm(t_rtv *paint, int fd)
{
	char	*num_width;
	char	*num_heigth;

	num_width = ft_itoa(paint->width);
	num_heigth = ft_itoa(paint->height);
	ft_putstr_fd("P6 ", fd);
	ft_putstr_fd(num_width, fd);
	ft_putstr_fd(" ", fd);
	ft_putstr_fd(num_heigth, fd);
	ft_putendl_fd(" 255", fd);
	free(num_width);
	free(num_heigth);
}

void	save_ppm_file(t_rtv *paint)
{
	int				fd;
	unsigned char	image[paint->width * paint->height * 3];
	char			*file_name;

	file_name = NULL;
	file_name = create_name_file(paint->name_file, ".ppm");
	if ((fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) <= 0)
		ft_exit(ERR_FILE_OPEN);
	copy_pixel_ppm(image, paint->draw, paint->width * paint->height);
	/* PPM header info, including the size of the image */
	create_header_ppm(paint, fd);
	write(fd, image, paint->width * paint->height * 3);
	/* Write the image data to the file - remember 3 byte per pixel */
	free(file_name);
	close(fd);
}


// char	*create_magic_num_old(t_rtv *paint)
// {
// 	char *num_width;
// 	char *num_heigth;
// 	char *magic_num;
// 	char *tmp;

// 	num_width = ft_itoa(paint->width);
// 	num_heigth = ft_itoa(paint->height);
// 	tmp = ft_strjoin("P6 ", num_width);
// 	magic_num = ft_strjoin(tmp, " ");
// 	free(tmp);
// 	tmp = ft_strjoin(magic_num, num_heigth);
// 	free(magic_num);
// 	magic_num = ft_strjoin(tmp, " 255");
// 	free(tmp);
// 	free(num_width);
// 	free(num_heigth);
// 	return (magic_num);
// }

// void	save_ppm_file_old(t_rtv *paint)
// {
// 	FILE *fd;
// 	unsigned char image[paint->width * paint->height * 3];
// 	const char *name_file;
// 	char *file_name;
// 	char *magic_num;

// 	file_name = NULL;
// 	name_file = paint->name_file;
// 	file_name = create_name_file(name_file);

// 	magic_num = create_magic_num_old(paint);
// 	/* Open file for writing */
// 	fd = fopen(file_name, "wb");
// 	copy_pixel(image, paint->draw, paint->width * paint->height);
	
// 	/* PPM header info, including the size of the image */
// 	// fprintf(fd, "P6 %d %d %d\n", paint->width, paint->height, 255);
// 	fprintf(fd, "%s\n", magic_num);

// 	/* Write the image data to the file - remember 3 byte per pixel */
// 	// write(fd, image, paint->width * paint->height);
// 	fwrite(image, 3, paint->width * paint->height, fd);
// 	free(file_name);
// 	/* Make sure you close the file */
// 	fclose(fd);
// }
