#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/utsname.h>
#define z printf
#define y char
void v(){y k[64];y*t;FILE*p=fopen("/etc/os-release","r");while(fgets(k,63,p)){if(strstr(k,"PRETTY_NAME")){t=strtok(k,"\"");t=strtok(NULL,"\"");z("%s\n",t);}}return;}y*t;bool a(long*c){FILE*b=fopen("/proc/uptime","r");double d;if(fscanf(b,"%lf",&d)!=1){fclose(b);return false;}fclose(b);*c=(long)d;return true;}void e(long c){int f=c/(60*60*24);int g=(c%(60*60*24))/(60*60);int h=(c%(60*60))/60;if(f>0){z("%dd ",f);}if(g>0){z("%dh ",g);}z("%dm\n",h);}void i(){FILE*b=fopen("/proc/meminfo", "r");y j[256];int l=0;int m=0;while(fgets(j,sizeof(j),b)){if(strncmp(j,"MemTotal:",9)==0){sscanf(j+9,"%d",&l);}else if(strncmp(j,"MemAvailable:",8)==0){sscanf(j+13,"%d",&m);}}fclose(b);z("%.2fMiB/%.2fMiB\n",(double)(l-m)/1024,(double)l/1024);}y*n="        ";struct utsname q;int main(int argc,y**argv){uname(&q);y*s=getenv("USER");long int u=sysconf(_SC_NPROCESSORS_ONLN);long c=0;z("  .-.   %s@%s\n  oo|   :3\n /`'\\   OS>",s,q.nodename);v();z("(\\_;/)  HOST>%s\n%sSH>%s\n%sKERN>%s %s %s\n%sCORES>%ld\n%s",q.nodename,n,getenv("SHELL"),n,q.sysname,q.release,q.machine,n,u,n);if(a(&c)){z("UP>");e(c);}z("%sMEM>",n);i();}