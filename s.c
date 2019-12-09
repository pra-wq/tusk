    1. Crc
C code


#include<stdio.h>
int a[100],b[100],i,j,k,len,count=0;
int gp[]={1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1};
int main()
{
void div(); system("clear");
printf("\n Enter the length of data frame \n"); scanf("%d",&len);
printf("Enter the message: \n"); for(i=0;i<len;i++) scanf("%d",&a[i]); for(i=0;i<16;i++)
a[len++]=0; for(i=0;i<len;i++) b[i]=a[i];
k=len-16; div();
for(i=0;i<len;i++) b[i]=b[i]^a[i];
printf("\n Data to be transmitted: \n"); for(i=0;i<len;i++)
printf("%2d",b[i]);
printf("\n Enter the received data: "); for(i=0;i<len;i++)
scanf("%d",&a[i]); div(); for(i=0;i<len;i++) if(a[i]!=0)
{
printf("\n Error in received data"); return 0;
}
printf("Data received is error free \n");
}
void div()
{
for(i=0;i<k;i++)
{
if(a[i]==gp[0])
{
for(j=i;j<17+i;j++) a[j]=a[j]^gp[count++];
}
count=0;
}
}
    2. Server socket

#include<stdio.h> #include<sys/types.h> #include<sys/socket.h> #include<netinet/in.h> #include<arpa/inet.h> #include<fcntl.h> #include<string.h>  #define SERV_TCP_PORT 6880
#define SERV_HOST_ADDR "127.0.0.1"

int main()
{
int sockfd,newsockfd,clilen;
struct sockaddr_in cli_addr,serv_addr; char filename[25],buf[1000];
int n,m; int fd;

if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0) printf("server: can't open stream socket\n"); else
printf("server: stream socket opened successfully\n"); serv_addr.sin_family=AF_INET; serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); serv_addr.sin_port=htons(SERV_TCP_PORT);
if((bind(sockfd,(struct sockaddr*) & serv_addr,sizeof(serv_addr)))<0) printf("server: can't bind to local address\n");
else
printf("server:bound to local address\n"); listen(sockfd,5);
printf("\n SERVER:waiting for client	\n");
for(;;)
{
clilen=sizeof(cli_addr);
newsockfd=accept(sockfd,(struct sockaddr*) & cli_addr,&clilen); if(newsockfd<0)
printf("server:accept error\n"); else printf("server:accepted\n"); n=read(newsockfd,filename,25); filename[n]='\0';
printf("\n SERVER:%s is found and ready to transfer\n",filename); fd=open(filename,O_RDONLY);
n=read(fd,buf,1000); buf[n]='\0'; write(newsockfd,buf,n); printf("\n transfer success\n"); close(newsockfd);

}
}
Client socket

#include<stdio.h> #include<sys/types.h> #include<sys/socket.h> #include<netinet/in.h> #include<arpa/inet.h> #include<fcntl.h> #include<string.h>  #define SERV_TCP_PORT 6880
#define SERV_HOST_ADDR "127.0.0.1"

int main()
{
int sockfd;
struct sockaddr_in serv_addr,cli_addr; char filename[25],buf[1000];
int n;

serv_addr.sin_family=AF_INET; serv_addr.sin_addr.s_addr=inet_addr(SERV_HOST_ADDR); serv_addr.sin_port=htons(SERV_TCP_PORT); if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0) printf("client: can't open stream socket\n");
else
printf("client: stream socket opened successfully\n");

if((connect(sockfd,(struct sockaddr*) & serv_addr,sizeof(serv_addr)))<0) printf("client: can't connect to server\n");
else
printf("client:connected to server successfully\n"); printf("enter the filename to be displayed:"); scanf("%s",filename); write(sockfd,filename,strlen(filename));
printf("\n filename transferred to server\n"); n=read(sockfd,buf,1000);
if(n<0)
printf("error reading from socket\n");
printf("client: displaying the file content of %s\n",filename); fputs(buf,stdout);
close(sockfd);

}
    3. Server fifo

#include<stdio.h> #include<fcntl.h> #include<stdlib.h> #include<string.h> #include<sys/types.h> #include<sys/stat.h> #include<unistd.h> int main()
{
char filename[100],buf[300],buf1[300]; int num,num2,n,filesize,f1,fd,fd2; mknod("fifo1",S_IFIFO | 0666,0);
mknod("fifo2",S_IFIFO | 0666,0); printf("\n server online\n"); fd=open("fifo1",O_RDONLY);
printf("client online...waiting for request\n\n"); while(1)
{
num=read(fd,filename,100); filename[num]='\0'; f1=open(filename,O_RDONLY);
printf("\n server:%s is found ...transferring the contents\n",filename); filesize=lseek(f1,0,2);
printf("filre size	is %d\n",filesize); lseek(f1,0,0); n=read(f1,buf1,filesize);  buf1[n]='\0'; fd2=open("fifo2",O_WRONLY); write(fd2,buf1,strlen(buf1));
printf("\n server:transfer completed\n"); exit(1);
}
unlink("fifo1");
unlink("fifo2");
}
Client fifo

#include<stdio.h> #include<fcntl.h> #include<string.h> #include<stdlib.h> #include<sys/types.h> #include<sys/stat.h> #include<unistd.h> int main()
{
char  filename[100],buf[300]; int num,num2,f1,fd,fd2; mknod("fifo1",S_IFIFO | 0666,0);
mknod("fifo2",S_IFIFO | 0666,0); fd=open("fifo1",O_WRONLY);
printf("client online..\n client:enter the path \n\n"); scanf("%s",filename); write(fd,filename,strlen(filename));
printf("\n waiting for reply\n"); fd2=open("fifo2",O_RDONLY); num2=read(fd2,buf,300); buf[num2]='\0';
printf("\n file received..the contents are ...\n"); fputs(buf,stdout);
unlink("fifo1");
unlink("fifo2"); exit(1);
}
    4. #include<stdlib.h>	<DISTANCE VECTOR>
#include<stdio.h> void rout_table();
int d[10][10],via[10][10];
int i,j,k,l,m,n,g[10][10],temp[10][10],ch,cost; int main()
{
system("clear");
printf("enter the values of no of nodes\n"); scanf("%d",&n);
rout_table(); for(i=0;i<n;i++) for(j=0;j<n;j++)
temp[i][j]=g[i][j]; for(i=0;i<n;i++) for(j=0;j<n;j++) via[i][j]=i; while(1)
{
for(i=0;i<n;i++) for(j=0;j<n;j++) if(d[i][j]) for(k=0;k<n;k++) if(g[i][j]+g[j][k]<g[i][k])
{
g[i][k]=g[i][j]+g[j][k]; via[i][k]=j;
}
for(i=0;i<n;i++)
{
printf("table for router %c\n",i+97); for(j=0;j<n;j++)
printf("%c::%d via %c\n",j+97,g[i][j],via[i][j]+97);
}
break;
}}
void rout_table()
{
printf("\n enter the routing table:\n"); printf("\t");
for(i=1;i<=n;i++) printf("%c\t",i+96); printf("\n"); for(i=0;i<n;i++)
printf("	");
printf("\n"); for(i=0;i<n;i++)
{


{


}}}
printf("%c",i+97); for(j=0;j<n;j++)

scanf("%d",&g[i][j]); if(g[i][j]!=999)
d[i][j]=1;
    5. RSA
#include<math.h> #include<stdlib.h> #include<stdio.h> #include<string.h>  int gcd(long m,long n)
{
while(n!=0)
{
long r=m%n; m=n;
n=r;
}
return m;
}
int rsa(char message[50])
{
long p=0,q=0,n=0,e=0,d=0,phi=0; long nummes[100]={0};
long encrypted[100]={0},decrypted[100]={0}; long i=0,j=0,nofelem=0;

printf("\nenter value of p and q\n"); scanf("%ld%ld",&p,&q);
n=p*q;
phi=(p-1)*(q-1);

for(i=2;i<phi;i++) if(gcd(i,phi)==1) break; e=i;

for(i=2;i<phi;i++) if((e*i-1)%phi==0)break; d=i;
for(i=0;i<strlen(message);i++) nummes[i]=message[i]-96; nofelem=strlen(message);

for(i=0;i<nofelem;i++)
{
encrypted[i]=1; for(j=0;j<e;j++)
encrypted[i]=(encrypted[i]*nummes[i])%n;
}
printf("\n Encrypted messagel\n"); for(i=0;i<nofelem;i++);
{
printf("%ld",encrypted[i]); printf("%c",(char)(encrypted[i])+96);
}
for(i=0;i<nofelem;i++)
{
decrypted[i]=1; for(j=0;j<d;j++)
decrypted[i]=(decrypted[i]*encrypted[i])%n;
}
printf("\n Decrypted messagei\n"); for(i=0;i<nofelem;i++) printf("%c",(char)(decrypted[i]+96)); return 0;
}
int main()
{
char msg[10];

printf("Enter The Message To Be Encrypted n"); scanf("%s",msg);
rsa(msg); return 0;
}





6.LKB

#include<stdio.h> #include<string.h> int min(int x, int y)
{
if(x<y) return x; else return y;
}
int main()
{
int drop=0,mini,nsec,cap,count=0,i,inp[25],process; system("clear");
printf("enter the bucket site\n"); scanf("%d",&cap);
printf("enter the operation rate\n"); scanf("%d",&process);
printf("enter the no. of seconds you want to stimulate\n"); scanf("%d",&nsec);
for(i=0;i<nsec;i++)
{
printf("enter the state of the packet enter at %d sec\n",i+1); scanf("%d",&inp[i]);
}
printf("\nsecond|packet recieved|packet sent|packet left|packet dropped|\n");
printf(".	\n");
for(i=0;i<nsec;i++)
{
count+=inp[i]; if(count>cap)
{
drop=count-cap; count=cap;
}
printf("%d",i+1);
printf("\t%d",inp[i]); mini=min(count,process); printf("\t\t%d",mini); count=count-mini; printf("\t\t%d",count); printf("\t\t%d\n",drop); drop=0;
}
for(;count!=0;i++)
{
if(count>cap)
{
drop=count-cap; count=cap;
}
printf("%d",i+1);
printf("\t0"); mini=min(count,process); printf("\t\t%d",mini); count=count-mini; printf("\t\t%d",count); printf("\t\t%d\n",drop);
}
}
SIMULATION
1.
# Simulation parameters setup	<TCL file>
set val(stop) 6.0 ; # stopping time of the simulation

# Initialization #Create a ns simulator set ns [new Simulator]

#Open the NS trace file  set tracefile [open 1.tr w]
$ns trace-all $tracefile

#Open the NAM trace file set namfile [open 1.nam w]
$ns namtrace-all $namfile

# Nodes Definition #Create 3 nodes set n1 [$ns node] set n2 [$ns node] set n3 [$ns node]

# Links Definition #Createlinks between nodes
$ns duplex-link $n1 $n2 1000Kb 60ms DropTail
$ns queue-limit $n1 $n2 14
$ns duplex-link $n2 $n3 500Kb 60ms DropTail
$ns queue-limit $n2 $n3 4
$ns duplex-link-op $n1 $n2 queuePos 0.5
$ns duplex-link-op $n2 $n3 queuePos 0.2

# Agents Definition #Setup a TCP connection set tcp0 [new Agent/TCP]
$ns attach-agent $n1 $tcp0 set sink1 [new Agent/TCPSink]
$ns attach-agent $n3 $sink1
$ns connect $tcp0 $sink1
$tcp0 set packetSize_ 1500

# Applications Definition
#Setup a FTP Application over TCP connection set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
$ns at 0.2 "$ftp0 start"
$ns at 5.0 "$ftp0 stop"

# Termination
#Define a 'finish' procedure proc finish {} {
global ns tracefile namfile
$ns flush-trace
close $tracefile close $namfile exec nam 1.nam & exit 0
}

$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "finish"
$ns at $val(stop) "puts \"done\" ; $ns halt"
$ns run

-------------------------------------------------------------------------

Awk file

BEGIN {
count=0; total=0;
}
{
event=$1; if(event=="d") { count++;
}
}  END {
printf("No of packets dropped : %d\n",count);
}
2.
# Simulation parameters setup
set val(stop) 10.0 ; # stopping time of the simulation

# Initialization #Create a ns simulator set ns [new Simulator]

#Open the NS trace file  set tracefile [open 2.tr w]
$ns trace-all $tracefile

#Open the NAM trace file set namfile [open 2.nam w]
$ns namtrace-all $namfile

# Nodes Definition #Create 3 nodes set n0 [$ns node] set n1 [$ns node] set n2 [$ns node] set n3 [$ns node] set n4 [$ns node] set n5 [$ns node] set n6 [$ns node]

# Links Definition #Createlinks between nodes
$ns duplex-link $n0 $n1 1mb 50ms DropTail
$ns queue-limit $n0 $n1 50
$ns duplex-link $n0 $n3 1mb 50ms DropTail
$ns queue-limit $n0 $n3 50
$ns duplex-link $n0 $n4 1mb 50ms DropTail
$ns queue-limit $n0 $n4 50
$ns duplex-link $n0 $n5 1mb 50ms DropTail
$ns queue-limit $n0 $n5 2
$ns duplex-link $n0 $n2 1mb 50ms DropTail
$ns queue-limit $n0 $n2 2
$ns duplex-link $n0 $n6 1mb 50ms DropTail
$ns queue-limit $n0 $n6 1

$ns duplex-link-op $n0 $n1 orient right-up
$ns duplex-link-op $n0 $n2 orient right
$ns duplex-link-op $n0 $n3 orient right-down
$ns duplex-link-op $n0 $n4 orient left-down
$ns duplex-link-op $n0 $n5 orient left
$ns duplex-link-op $n0 $n6 orient left-up

Agent/Ping instproc recv {from rtt} {
$self instvar node_
puts "node [$node_ id] recived ping answer from $from with round-trip- time $rtt ms."
}

set p1 [new Agent/Ping] set p2 [new Agent/Ping] set p3 [new Agent/Ping] set p4 [new Agent/Ping] set p5 [new Agent/Ping] set p6 [new Agent/Ping]

$ns attach-agent $n1 $p1
$ns attach-agent $n2 $p2
$ns attach-agent $n3 $p3
$ns attach-agent $n4 $p4
$ns attach-agent $n5 $p5
$ns attach-agent $n6 $p6

$ns connect $p1 $p4
$ns connect $p2 $p5
$ns connect $p3 $p6

$ns at 0.2 "$p1 send"
$ns at 0.4 "$p2 send"
$ns at 0.6 "$p3 send"
$ns at 1.0 "$p4 send"
$ns at 1.2 "$p5 send"
$ns at 1.4 "$p6 send"

# Termination
#Define a 'finish' procedure proc finish {} {
global ns tracefile namfile
$ns flush-trace close $tracefile close $namfile exec nam 2.nam & exit 0
}

$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "finish"
$ns at $val(stop) "puts \"done\" ; $ns halt"
$ns run
--------------------------------------------------------------------- BEGIN {
count=0;
}
{
event=$1; if(event=="d") { count++;
}
}  END {
printf("No of packets dropped : %d\n",count);
}
3.
# Simulation parameters setup
set val(stop) 10.0 ;# time of simulation end

# Initialization #Create a ns simulator set ns [new Simulator]

#Open the NS trace file  set tracefile [open 5.tr w]
$ns trace-all $tracefile

#Open the NAM trace file set namfile [open 5.nam w]
$ns namtrace-all $namfile
$ns color 1 Blue
$ns color 2 Red

# Nodes Definition #Create 9 nodes set n0 [$ns node] set n1 [$ns node] set n2 [$ns node] set n3 [$ns node] set n4 [$ns node] set n5 [$ns node] set n6 [$ns node] set n7 [$ns node] set n8 [$ns node]

# Create LAN
$ns make-lan "$n3 $n4 $n5 $n6 $n7 $n8" 512Kb 50ms LL Queue/DropTail

# Links Definition #Createlinks between nodes
$ns duplex-link $n1 $n0 2.0Mb 50ms DropTail
$ns queue-limit $n1 $n0 50
$ns duplex-link $n2 $n0 2.0Mb 50ms DropTail
$ns queue-limit $n2 $n0 50
$ns duplex-link $n0 $n3 1.0Mb 50ms DropTail
$ns queue-limit $n0 $n3 7 #Give node position (for NAM)
$ns duplex-link-op $n1 $n0 orient right-down
$ns duplex-link-op $n2 $n0 orient right-up
$ns duplex-link-op $n0 $n3 orient right

# Agents Definition
#Setup a TCP/Reno connection set tcp0 [new Agent/TCP/Reno]
$ns attach-agent $n1 $tcp0 set sink1 [new Agent/TCPSink]
$ns attach-agent $n7 $sink1
$ns connect $tcp0 $sink1
$tcp0 set packetSize_ 1500
$tcp0 set class_ 1
set tfile1 [open cwnd1.tr w]
$tcp0 attach $tfile1
$tcp0 trace cwnd_

#Setup a TCP/Vegas connection set tcp5 [new Agent/TCP/Vegas]
$ns attach-agent $n2 $tcp5 set sink6 [new Agent/TCPSink]
$ns attach-agent $n8 $sink6
$ns connect $tcp5 $sink6
$tcp5 set packetSize_ 1500
$tcp5 set class_ 2
set tfile2 [open cwnd2.tr w]
$tcp5 attach $tfile2
$tcp5 trace cwnd_

# Applications Definition
#Setup a FTP Application over TCP/Reno connection set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
$ns at 0.3 "$ftp0 start"
$ns at 8.0 "$ftp0 stop"

#Setup a FTP Application over TCP/Vegas connection set ftp4 [new Application/FTP]
$ftp4 attach-agent $tcp5
$ns at 0.3 "$ftp4 start"
$ns at 8.0 "$ftp4 stop"

# Termination
#Define a 'finish' procedure proc finish {} {
global ns tracefile namfile
$ns flush-trace close $tracefile close $namfile exec nam 5.nam & exit 0
}

$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "finish"
$ns at $val(stop) "puts \"done\" ; $ns halt"
$ns run


BEGIN{}
{
if($6=="cwnd_")
{ printf("%f\t%f\n",$1,$7); }
} END{}
4.
# Simulation parameters setup
set val(chan) Channel/WirelessChannel	;# channel type
set val(prop) Propagation/TwoRayGround	;# radio-propagation model set val(netif) Phy/WirelessPhy		;# network interface type set val(mac) Mac/802_11	;# MAC type
set val(ifq) Queue/DropTail/PriQueue	;# interface queue type set val(ll) LL	;# link layer type
set val(ant) Antenna/OmniAntenna	;# antenna  model set val(ifqlen) 50	;# max packet in ifq
set val(nn) 2		;# number of mobilenodes set val(rp) DSDV	;# routing protocol
set val(x) 700	;# X dimension of topography
set val(y) 444	;# Y dimension of topography
set val(stop) 10.0	;# time of simulation end

# Initialization #Create a ns simulator set ns [new Simulator]

#Setup topography object set topo [new Topography]
$topo load_flatgrid $val(x) $val(y) create-god $val(nn)

#Open the NS trace file  set tracefile [open 4.tr w]
$ns trace-all $tracefile

#Open the NAM trace file  set namfile [open out.nam w]
$ns namtrace-all $namfile
$ns namtrace-all-wireless $namfile $val(x) $val(y) set chan [new $val(chan)];#Create wireless channel

# Mobile node parameter setup
$ns node-config -adhocRouting	$val(rp) \
-llType	$val(ll) \
-macType	$val(mac) \
-ifqType	$val(ifq) \
-ifqLen	$val(ifqlen) \
-antType	$val(ant) \
-propType	$val(prop) \
-phyType	$val(netif) \
-channel	$chan \
-topoInstance	$topo \
-agentTrace	ON \
-routerTrace	ON \
-macTrace	ON \
-movementTrace	ON
# Nodes Definition #Create 2 nodes set n0 [$ns node]
$n0 set X_ 268
$n0 set Y_ 339
$n0 set Z_ 0.0
$ns initial_node_pos $n0 20 set n1 [$ns node]
$n1 set X_ 428
$n1 set Y_ 344
$n1 set Z_ 0.0
$ns initial_node_pos $n1 20

# Generate movement
$ns at .1 " $n0 setdest 600 344 100 "
$ns at .1 " $n1 setdest 300 339 100 "

# Agents Definition #Setup a TCP connection set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0 set sink1 [new Agent/TCPSink]
$ns attach-agent $n1 $sink1
$ns connect $tcp0 $sink1
$tcp0 set packetSize_ 1500

# Applications Definition
#Setup a FTP Application over TCP connection set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
$ns at 1.0 "$ftp0 start"
$ns at 5.0 "$ftp0 stop"

#Define a 'finish' procedure proc finish {} {
global ns tracefile namfile
$ns flush-trace close $tracefile close $namfile exec nam out.nam & exit 0
}
for {set i 0} {$i < $val(nn) } { incr i } {
$ns at $val(stop) "\$n$i reset"
}

$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "finish"
$ns at $val(stop) "puts \"done\" ; $ns halt"
$ns run
----------------------------------------------------------------



BEGIN{
count=0; total=0;
}
{
event =$1; if(event=="D") { count++;
}
} END{
printf("No of packets dropped : %d\n",count);
}
5.
# Simulation parameters setup
set set
set
val(chan) val(prop)
val(netif)
Channel/WirelessChannel Propagation/TwoRayGround
Phy/WirelessPhy
;#
;#
;#
channel type
radio-propagation model
network interface type
set
val(mac)
Mac/802_11
;#
MAC type
set
val(ifq)
Queue/DropTail/PriQueue
;#
interface queue type
set
val(ll)
LL
;#
link layer type
set
val(ant)
Antenna/OmniAntenna
;#
antenna model
set
val(ifqlen)
50
;#
max packet in ifq
set
val(nn)
7
;#
number of mobilenodes
set
val(rp)
AODV
;#
routing protocol
set
val(x)
1151
;#
X dimension of topography
set
val(y)
900
;#
Y dimension of topography
set
val(stop)
10.0
;#
time of simulation end

# Initialization #Create a ns simulator set ns [new Simulator]

#Setup topography object set topo [new Topography]
$topo load_flatgrid $val(x) $val(y) create-god $val(nn)

#Open the NS trace file
set tracefile [open out.tr w]
$ns trace-all $tracefile

#Open the NAM trace file  set namfile [open out.nam w]
$ns namtrace-all $namfile
$ns namtrace-all-wireless $namfile $val(x) $val(y) set chan [new $val(chan)];#Create wireless channel

# Mobile node parameter setup
$ns node-config -adhocRouting	$val(rp) \
-llType	$val(ll) \
-macType	$val(mac) \
-ifqType	$val(ifq) \
-ifqLen	$val(ifqlen) \
-antType	$val(ant) \
-propType	$val(prop) \
-phyType	$val(netif) \
-channel	$chan \
-topoInstance	$topo \
-agentTrace	ON \
-routerTrace	ON \
-macTrace	ON \
-movementTrace ON

# Nodes Definition #Create 7 nodes

set
$n0
$n0
$n0
$ns
n0 [$ns node] set X_ 338
set Y_ 305
set Z_ 0.0 initial_node_pos



$n0



20
set
$n1
$n1
$n1
$ns
n1 [$ns node] set X_ 527
set Y_ 300
set Z_ 0.0 initial_node_pos




$n1




20
set
$n2
$n2
$n2
$ns
n2 [$ns node] set X_ 672
set Y_ 305
set Z_ 0.0 initial_node_pos




$n2




20
set
$n3
$n3
$n3
$ns
n3 [$ns node] set X_ 867
set Y_ 304
set Z_ 0.0 initial_node_pos




$n3




20
set
$n4
$n4
$n4
$ns
n4 [$ns node] set X_ 1051
set Y_ 302
set Z_ 0.0 initial_node_pos




$n4




20
set
$n5
$n5
$n5
$ns
n5 [$ns node] set X_ 292
set Y_ 438
set Z_ 0.0 initial_node_pos




$n5




20
set
$n6
$n6
$n6
$ns
n6 [$ns node] set X_ 349
set Y_ 58
set Z_ 0.0
initial_node_pos




$n6




20

# Generate movement
$ns at 1 " $n6 setdest 890 58 75 "

# Agents Definition #Setup a TCP connection set tcp0 [new Agent/TCP]
$ns attach-agent $n5 $tcp0 set sink1 [new Agent/TCPSink]
$ns attach-agent $n6 $sink1
$ns connect $tcp0 $sink1
$tcp0 set packetSize_ 1500
# Applications Definition
#Setup a FTP Application over TCP connection set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
$ns at 1.0 "$ftp0 start"
$ns at 10.0 "$ftp0 stop"

# Termination
#Define a 'finish' procedure proc finish {} {
global ns tracefile namfile
$ns flush-trace close $tracefile close $namfile exec nam out.nam & exit 0
}

for {set i 0} {$i < $val(nn) } { incr i } {
$ns at $val(stop) "\$n$i reset"
}

$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "finish"
$ns at $val(stop) "puts \"done\" ; $ns halt"
$ns run


BEGIN{
count1=0 pack1=0 time1=0
}
{
if($1=="r" && $3=="_5_" && $4=="AGT")
{
count1++ pack1=pack1+$8 time1=$2
}
} END{
printf("The Throughput from n5 to n6: %f Mbps \n", ((count1*pack1*8)/(time1*1000000)));
}
6.
set opt(ecn) 0  ; set opt(window) 30 ; # Topology
set opt(type) gsm ; #type of link:
# AQM parameters set opt(minth) 5 ; set opt(maxth) 10 ;
set opt(adaptive) 1 ; # 1 for Adaptive RED, 0 for plain RED #default downlink bandwidth in bps
set bwDL(gsm) 9600
#default uplink bandwidth in bps set bwUL(gsm) 9600
#default downlink propagation delay in seconds set propDL(gsm) .500
#default uplink propagation delay in seconds set propUL(gsm) .500
#default buffer size in packets set buf(gsm) 10

set ns [new Simulator] set tf [open out.tr w] set nf [open out1.nam w]
$ns trace-all $tf
$ns namtrace-all $nf set nodes(s) [$ns node]
set nodes(bs1) [$ns node] set nodes(ms) [$ns node] set nodes(bs2) [$ns node] set nodes(d) [$ns node]

proc cell_topo {} { global ns nodes
$ns duplex-link $nodes(s) $nodes(bs1) 3Mbps 10ms DropTail
$ns duplex-link $nodes(bs1) $nodes(ms) 1Mbps 1ms RED
$ns duplex-link $nodes(ms) $nodes(bs2) 1Mbps 1ms RED
$ns duplex-link $nodes(bs2) $nodes(d) 3Mbps 50ms DropTail puts "cell Topology"
}

proc set_link_params {t} {
global ns nodes bwUL bwDL propUL propDL buf
$ns bandwidth $nodes(bs1) $nodes(ms) $bwDL($t) simplex
$ns bandwidth $nodes(ms) $nodes(bs1) $bwUL($t) simplex
$ns bandwidth $nodes(bs2) $nodes(ms) $bwDL($t) simplex
$ns bandwidth $nodes(ms) $nodes(bs2) $bwUL($t) simplex
$ns delay $nodes(bs1) $nodes(ms) $propDL($t) simplex
$ns delay $nodes(ms) $nodes(bs1) $propDL($t) simplex
$ns delay $nodes(bs2) $nodes(ms) $propDL($t) simplex
$ns delay $nodes(ms) $nodes(bs2) $propDL($t) simplex
$ns queue-limit $nodes(bs1) $nodes(ms) $buf($t)
$ns queue-limit $nodes(ms) $nodes(bs1) $buf($t)
$ns queue-limit $nodes(bs2) $nodes(ms) $buf($t)
$ns queue-limit $nodes(ms) $nodes(bs2) $buf($t)
}
# RED and TCP parameters Queue/RED set summarystats_ true
Queue/DropTail set summarystats_ true Queue/RED set adaptive_ $opt(adaptive) Queue/RED set q_weight_ 0.0
Queue/RED set thresh_ $opt(minth) Queue/RED set maxthresh_ $opt(maxth) Queue/DropTail set shrink_drops_ true Agent/TCP set ecn_ $opt(ecn) Agent/TCP set window_ $opt(window) DelayLink set avoidReordering_ true

#Create topology switch $opt(type) {
gsm - gprs - umts {cell_topo}
}

set_link_params $opt(type)
$ns insert-delayer $nodes(ms) $nodes(bs1) [new Delayer]
$ns insert-delayer $nodes(bs1) $nodes(ms) [new Delayer]
$ns insert-delayer $nodes(ms) $nodes(bs2) [new Delayer]
$ns insert-delayer $nodes(bs2) $nodes(ms) [new Delayer]

# Set up forward TCP connection
set tcp1 [$ns create-connection TCP/Sack1 $nodes(s) TCPSink/Sack1
$nodes(d) 0]
set ftp1 [[set tcp1] attach-app FTP]
$ns at 0.5 "$ftp1 start" proc stop {} {
global nodes ns opt nf tf
$ns flush-trace close  $nf close $tf
exec nam out1.nam & exit 0
}
$ns at 100 "stop"
$ns run
----------------------------------------------------------------------- BEGIN {
PacketRcvd=0; Throughput=0.0;
}
{
if(($1=="r") && ($5=="tcp") && ($10=4.0))
{
PacketRcvd++;
}} END {
Throughput=((PacketRcvd*1000*8)/(95.0*1000000)); printf("packet received:%f\n", PacketRcvd); printf( "the throughput is:%f\n",Throughput);
}
