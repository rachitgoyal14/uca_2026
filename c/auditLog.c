#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define LOGFILE "audit.log"
#define BUF_SIZE 1024

void print_str(const char *s){
	write(1,s,strlen(s));
}

void int_to_str(int num, char *buf){
	int i = 0,j;
	char temp[20];
	if(num == 0){
		buf[0] = '0';
		buf[1] = '\0';
		return;
	}
	
    while(num > 0){
		temp[i++] = (num%10) + '0';
		num /= 10;
	}

	for (j = 0;j < i;j++){
		buf[j] = temp[i-j-1];
	}

	buf[i] = '\0';
}

int main(int argc, char *argv[]){

	if(argc < 2){
		print_str("Usage:\n");
		print_str("  ./auditlog --add \"message\"\n");
		print_str("  ./auditlog --view\n");
		return 1;
	}

	if(strcmp(argv[1], "--add") == 0){
		if(argc != 3){
			print_str("Usage: ./auditlog --add \"message\"\n");
			return 1;
		}
		int fd = open(LOGFILE,O_WRONLY | O_CREAT | O_APPEND, 0644);
		if(fd < 0){
			print_str("Error opening log file.\n");
			return 1;
		}
		write(fd, argv[2],strlen(argv[2]));
		write(fd, "\n", 1);
		close(fd);
	}

	else if(strcmp(argv[1], "--view") == 0){
		int fd = open(LOGFILE,O_RDONLY);
		if(fd < 0){
			print_str("No Log File found.\n");
			return 1;
		}
		char buf[BUF_SIZE];
		char line[BUF_SIZE];
		int byteRead, linePos = 0, lineNo = 1;

		while((byteRead = read(fd,buf,BUF_SIZE)) > 0){
			for(int i = 0;i<byteRead;i++){
				line[linePos++] = buf[i];
				if(buf[i] == '\n'){
					char numbuf[20];
					int_to_str(lineNo++,numbuf);
					write(1,numbuf,strlen(numbuf));
					write(1,": ",2);
					write(1,line,linePos);
					linePos = 0;
				}
			}
		}

		if(linePos > 0){
			char numbuf[20];
			int_to_str(lineNo,numbuf);
			write(1,numbuf,strlen(numbuf));
			write(1,": ",2);
			write(1,line,linePos);
			write(1,"\n",1);
		}
		close(fd);
	}

	else{
		print_str("Unknown command.\n");
		print_str("Usage:\n");
		print_str("  ./auditlog --add \"message\"\n");
		print_str("  ./auditlog --view\n");
		return 1;
	}
    
	return 0;
}
	