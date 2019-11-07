#if environment_variables
    [root@localhost cmd_record]# export
    ...
    declare -x PATH="/usr/lib64/qt-3.3/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/root/bin"
    declare -x PWD="/mnt/hgfs/vmware_share/cmd_record"
    ...
    [root@localhost cmd_record]# env
    ...
    PATH=/usr/lib64/qt-3.3/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/root/bin
    PWD=/mnt/hgfs/vmware_share/cmd_record
    ...

    [root@localhost cmd_record]# echo $PATH
    /usr/lib64/qt-3.3/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/root/bin

    export PATH=/opt/STM/STLinux-2.3/devkit/sh4/bin:$PATH
    #vim ~/.bashrc
    export PATH="/opt/STM/STLinux-2.3/devkit/sh4/bin:$PATH"
    # vim /etc/profile
    export PATH="/opt/STM/STLinux-2.3/devkit/sh4/bin:$PATH"
    #source /etc/profile
#endif

#if find
	find /etc/ -name passwd      ##查找/etc/下名称中带有passwd的文件
	find /etc -maxdepth 1 -name passwd     ##查找/etc/下名称中带有passwd的文件，查找一层。
	find /etc -name *.conf       ##查找/etc/下名称中带有*.conf的文件(下面显示的是部分)
	find /etc -maxdepth 2 -name *.conf  ##查找/etc/下名称中带有*.conf的文件，且查找两层，包括一层（下面显示的是部分）
	find /etc -maxdepth 2 -mindepth 2 -name *.conf  ##查找/etc/下名称中带有*.conf的文件，且只查找第二层
	find /mnt -group tony             ##查找/mnt中所有组是tony用户的文件
	find /mnt -user student -group student  ##查找/mnt中所有人和所有组都是student的文件
	find /mnt -not -user student      ##查找/mnt中所有人不是student用户的文件
	find /mnt -not -user student -o -group tony   ##查找/mnt中所有人不是student用户或者所有组是tony用户的文件
	find /mnt -size 20K       ##查找/mnt文件大小近似20k的文件
	find /mnt -size +20K      ##查找/mnt文件大小大于20k的文件
	find /mnt -size -20K      ##查找/mnt文件大小小于20k的文件
	find /mnt -type d         ##按type查找/mnt中目录
	find /mnt -type f         ##按type查找/mnt中文件
	find /mnt -cmin 10        ##查找/mnt中十分钟左右修改的
	find /mnt -cmin +10       ##查找/mnt中十分钟以上修改的
	find /mnt -cmin -10       ##查找/mnt中十分钟以内修改的
	find /mnt -ctime 10       ##查找/mnt中十天左右修改的
	find /mnt -ctime +10      ##查找/mnt中十天以上修改的
	find /mnt -ctime -10      ##查找/mnt中十天以内修改的
	find /mnt/ -perm 444      ##查找/mnt文件权限为444的文件
	find /mnt/ -perm -444     ##查找/mnt中user有读的权限且group有读的权限且other有读的权限的文件。（三个条件，u.g.o至少要读的权限即r--r--r--）
	find /mnt/ -perm -004     ##查找/mnt中other有读权限的文件（一个条件,o至少有读的权限）
	find /mnt/ -perm -644     ##查找/mnt中user有读写的权限且group至少有读权限且other有读的权限的文件。（四个条件,rw-r--r--）
	find /etc/ -name *.conf -exec cp -rp {} /mnt \;   ##把/etc/目录下名称中带有.conf的文件递归复制到/mnt下
	find /mnt -name "*.conf" -exec rm -fr {} \; ##删除/mnt名称中带有.conf的文件
	find / -group mail -exec cp -rp {} /mnt \; ##把/目录下的组属于mail的文件复制到/mnt
#endif

#if last
    /var/log/wtmp
    [root@localhost cmd_record]# last
    root     pts/6        192.168.235.1    Mon Aug 12 10:37   still logged in
    root     pts/1        192.168.235.1    Fri Aug  9 13:46 - 10:03 (2+20:17)

    [root@localhost cmd_record]# last reboot
    reboot   system boot  3.10.0-327.el7.x Wed Jul 31 11:31 - 16:01 (22+04:29)
    reboot   system boot  3.10.0-327.el7.x Mon Jul  8 10:35 - 11:30 (23+00:54)
#endif

#if SElinux
    [root@localhost cmd_record]# /usr/sbin/sestatus -v
    SELinux status:                 enabled
    SELinuxfs mount:                /sys/fs/selinux
    SELinux root directory:         /etc/selinux

    [root@localhost cmd_record]# getenforce
    Permissive

    修改1：
    [root@localhost cmd_record]# setenforce 0
    修改2：
    vim /etc/sysconfig/selinux
    将 SELINUX=enforcing 改为 SELINUX=disabled
#endif

#if smb_cmd
    [root@bogon veda]# useradd sc_test
    [root@bogon veda]# passwd sc
    Changing password for user sc.
    [root@bogon veda]# pdbedit -L
    sc:1001:
    [root@bogon veda]# smbpasswd  -a sc
    New SMB password:
    Retype new SMB password:
    [root@bogon veda]# smbpasswd -a sc_test
    New SMB password:
    Retype new SMB password:
    Added user sc_test.
    [root@bogon veda]# pdbedit -L
    sc:1001:
    sc_test:1002:
    [root@bogon veda]# smbpasswd -x sc_test
    Deleted user sc_test.
    [root@bogon veda]# pdbedit -L
    sc:1001:
#end

#if iptables
    /*
    如果说你以前使用的是contos7那么默认使用的防火墙那么就是Firewall
    这样的话，先关闭Firewall
    */
    systemctl stop firewalld #关闭防火墙
    systemctl disable firewalld #禁止开机启动
    service iptables status

    iptables -F
    iptables -P INPUT DROP
    iptables -A INPUT -p tcp --dport 443 -j ACCEPT -i eth0_0

    iptables导致nginx反向代理不可用的解决方案
    在nginx反向代理、web服务器所在的同一系统上配置iptables进行访问限制时，
    可能会导致nginx反向代理不能正常工作。一种常见原因是iptables没有配置来
    自本机ip的连接权限而且默认是DROP策略。
    解决方法也很简单，添加本机ip的连接权限，例如：

    sudo iptables -A INPUT -p tcp --dport 80 -j ACCEPT
    sudo iptables -A INPUT -p tcp -s 127.0.0.1 -j ACCEPT
    sudo iptables -A INPUT -p tcp -s 10.212.193.58 -j ACCEPT
#end

#if patch
    diff -up linux-2.6.28.8/net/sunrpc/svc.orig.c linux-2.6.28.8/net/sunrpc/svc.c > patch

    diff -uparN linux-2.6.31.3 linux-2.6.31.3_1/ > mypatch
    cd linux-2.6.31.3
    patch -p1 < mypatch
#end

#if od
	od -tx1 -Ax foo2.o
	
     -t, --format=TYPE	select output format or formats
    [root@bogon home]# echo "a" | od -tx1
    0000000 61 0a
    0000002
    [root@bogon home]# echo "abc" | od -tx1
    0000000 61 62 63 0a
    0000004
    [root@bogon home]# echo "abc" | od -x
    0000000 6261 0a63
    0000004
#end

#if grep
    单个字符串进行查找：
    1、查找当前目录文件名中的字符串：    grep  字符串  文件名
    2、查找某个文件中字符串，并输出行号：grep -n 字符串 文件名
    3、查找当前目录（包含子目录）的字符串：grep -r 字符串 *
    4、查找当前目录（包含子目录）的字符串，并输出行号：grep -rn 字符串 *

    * :通配符，表示当前目录所有文件，也可以按照某种模式进行匹配，例如：
        grep 字符串 *.txt   匹配所有文件后缀名为txt的字符串

    -r ：递归查找
    -n ：显示行号
    -R ：查找所有文件包含子目录
    -i ：忽略大小写

    2、同时满足多个字符串查找：
    grep 字符串1 文件名| grep 字符串2|grep 字符串3|grep ...

    3、满足多个关键字之一
    grep -E "字符串1|字符串2|字符串3|"  文件名   或者
    egrep  "字符串1|字符串2|字符串3|"  文件名

    grep ^root /etc/passwd
    grep bash$ /etc/passwd
    grep ^$ /etc/shadow
    grep -rn "netlink.*\.h"
#endif

#if ip
    1、重命名网卡
    ip link set eth5_0 down
    ip link set eth5_0 name eno_sc_798
    ip link set eno_sc_798 up

    ifconfig eth0 down
    /*保留前3段 vendor*/
    ifconfig eth0 hw ether xx:xx:xx:xx:xx:xx
    ifconfig eth0 up

    :MACADDR=xx:xx:xx:xx:xx:xx
#endif

#if lspci ethtool
    -s [[[[<domain>]:]<bus>]:][<slot>][.[<func>]]
    -d [<vendor>]:[<device>]

    查看link状态：
    root@Magic-Environment:/proc/746# ethtool-2 eth1_0
    Settings for eth1_0:
        Supported ports: [ FIBRE ]
        Supported link modes:   1000baseT/Full
        Supports auto-negotiation: Yes
        Advertised link modes:  1000baseT/Full
        Advertised auto-negotiation: Yes
        Speed: N/A (0)
        Duplex: Half
        Port: FIBRE
        PHYAD: 255
        Transceiver: internal
        Auto-negotiation: on
        Link detected: no

    查看name对应的pcie地址:
    root@Magic-Environment:/proc/746# ethtool-2 -i eth1_0
    driver: net_e1000_igb
    version:
    firmware-version:
    bus-info: 0000:03:00.1
#end

#if scp
    /*从远程拷贝到本地*/
    scp user@A.B.C.D:${ROOTDIR}/ports/helloworld/helloworld /usr/admin/.
#end

#if gdb
    info sharedlibrary
    show sheduler-locking
    info var optind

    break <linespec> thread <threadno> if ...
    (gdb) break frik.c:13 thread 28 if bartab > lim
#end

taskset -a -p <vpe-pid>
pid 16251's current affinity mask: 2        # main thread
pid 16288's current affinity mask: ffffff   # DPDK interrupt thread (not bound to a core)
pid 16289's current affinity mask: 4        # stats thread
pid 16290's current affinity mask: 8        # worker thread 0
pid 16291's current affinity mask: 10       # worker thread 1

[root@localhost cmd_record]# which ifconfig
/usr/sbin/ifconfig
[root@localhost cmd_record]# whereis ifconfig
ifconfig: /usr/sbin/ifconfig /usr/share/man/man8/ifconfig.8.gz

mount -o remount,size=777M tmpfs /dev/shm
parted -l
df -h
fdisk -l
cfdisk

sed 's/要被取代的字串/新的字串/g'
rpm -e --nodeps java-1.6.0-openjdk-1.6.0.0-1.66.1.13.0.el6.i686
gcc -v main.c
ls -al *b.so
arp -a
ip neigh
ctrl+s 终止屏幕输出（即停止回显），你敲的依然有效，只是看不见，作用嘛，你登录系统输入密码时，是不是看不见你敲的东东
ctrl+q 恢复屏幕输出，你刚才敲的都显示出来了
