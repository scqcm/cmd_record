/*git配置*/:
#if git_config
yum install git
git init
git config --global color.ui true
git check-ignore -v App.class
git config --global alias.lg "log --color --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit"

[root@localhost cmd_record]# cat .git/config 
[core]
	repositoryformatversion = 0
	filemode = false
	bare = false
	logallrefupdates = true
	symlinks = false
	ignorecase = true
[remote "origin"]
	url = git@github.com:scqcm/cmd_record.git
	fetch = +refs/heads/*:refs/remotes/origin/*   */
[branch "master"]
	remote = origin
	merge = refs/heads/master

查看信息：
[root@localhost vpp]# git remote -v
origin	https://gerrit.fd.io/r/vpp (fetch)
origin	https://gerrit.fd.io/r/vpp (push)

git remote show origin

git config -l
[root@localhost cmd_record]# git branch -vv
* master 2b63991 [origin/master: ahead 1] move coding_style.c.

Push an existing Git repository:
cd existing_repo
git remote rename origin old-origin
git remote add origin git@gitlab.verify.com:hongmengOS/hm-verify-kernel.git
git push -u origin --all
git push -u origin --tags

1.配置秘钥
ssh-keygen -t rsa -C “注释” ，密码为空。生成两个文件：id_rsa和id_rsa.pub
在github上添加“id_rsa.pub”公钥。测试：
[root@localhost .ssh]# ssh git@192.168.2.201
PTY allocation request failed on channel 0
Welcome to GitLab, @sunchao!
Connection to 192.168.2.201 closed.

2.查看用户名和邮箱地址
git config --list
git config user.name
git config user.email

3.查看配置文件的位置
位置1:/etc/gitconfig
      系统级别的配置,适用于所有的用户和所有的库,可以使用 $git config --system 来指定和修改
位置2:~/.gitconfig
      用户级别的配置,适用于当前登录的用户,可以使用$git config --gloabal来指定和修改
位置3:.git/config
      库级别的配置,适用于某个具体的库,可以使用$git config来指定和修改,存储在具体的库隐藏的.git文件夹下
      说明:Git会优先使用库级别的配置,再然后是global级别的配置,最后是system级别的配置.
针对当前用户的配置：
git config --global user.email sunchao@appexnetworks.com
git config --global user.name sunchao
#endif

#if git 查看某个文件修改历史

显示文件的每一行是在那个版本最后修改:
git blame [file]

显示某个文件的每个版本提交信息：提交日期，提交人员，版本号，提交备注（没有修改细节）
<<<<<<< HEAD
git whatchanged [file]

显示某个版本的修改详情
git show 6edc4bdc
git log -p 6edc4bdc
git log --name-only 893db346
git log --name-status 893db346
git show 6edc4bdc [file]
git log --author="scqcm"
git show 6edc4bdc --stat

显示所有提交记录，每条记录只显示一行
git log --pretty=oneline [file]

显示与某个文件有关的所有提交记录
git log --pretty=oneline  charge.lua

显示某个版本的某个文件修改情况
git show 6edc4bdc [file]

回退单个文件
git reset  fcd2093 a.jsp

查看某个文件的详细变更历史：
git log --pretty=oneline [file] > cmd.sh
sed -i 's/ .*$/ [file]/g' cmd.sh
sed -i 's/^/git show /g' cmd.sh
chmod +x cmd.sh
./cmd.sh

#endif

#if git 冲突
git rebase master
    git status
    vim lw_ipset_config.c
    git add lw_ipset_config.c
    git status
git rebase --continue

git diff 3eaf0ee8 66709934 >sc.patch
patch -p1 < ../sc.patch
#endif

git pull = git fetch + git merge FETCH_HEAD
git pull --rebase =  git fetch + git rebase FETCH_HEAD

git clone https://user:code@github.com/scqcm/cmd_record.git ./target_dir
git clone git@118.190.200.88:LightWAN/ipset.git
git clone git@git.appexnetworks.com:LightWAN/ipset.git
git checkout FEA_v2.1_12721_ipsetHash
yum install dos2unix.x86_64

#if git remote
我们先删除已关联的名为origin的远程库：
git remote rm origin

然后，先关联GitHub的远程库：
git remote add github git@github.com:michaelliao/learngit.git

接着，再关联码云的远程库：
git remote add gitee git@gitee.com:liaoxuefeng/learngit.git

git remote -v
gitee	git@gitee.com:liaoxuefeng/learngit.git (fetch)
gitee	git@gitee.com:liaoxuefeng/learngit.git (push)
github	git@github.com:michaelliao/learngit.git (fetch)
github	git@github.com:michaelliao/learngit.git (push)

git push github master
git push gitee master
#endif

git clone git@118.190.200.88:LightWAN/ipset.git
git clone git@git.appexnetworks.com:LightWAN/ipset.git
git checkout FEA_v2.1_12721_ipsetHash
yum install dos2unix.x86_64 
dos2unix *.c *.h *.sh
sed -i 's/ *$//g' *.h *.c *.sh
git add src/lw_ipset_hashidx.*
git status
git commit -a
git commit --amend

git push origin FEA_v2.1_12721_ipsetHash
git pull

[root@localhost vpp]# git branch -a
  master
* stable/1810
  remotes/origin/HEAD -> origin/master
  remotes/origin/master
  ...
  remotes/origin/stable/1810

git checkout -b mybranch origin/mybranch
git checkout -b temp --track origin/xxx

[root@localhost vpp]# git checkout stable/1807 //git checkout -b stable/1807 origin/stable/1807
Branch stable/1807 set up to track remote branch stable/1807 from origin.
Switched to a new branch 'stable/1807'

/*删除分支*/
git branch -D FEA_v2.1_12721_ipsetHash_3003
/*删除远程分支*/
git push origin --delete FEA_v2.1_12721_ipsetHash_3003
/*新建分支*/
git checkout -b FEA_v2.1_12721_ipsetHash_3003
/*同步到远端*/
git push origin FEA_v2.1_12721_ipsetHash_3003

git diff --staged test.c
git diff --cached test.c
Git diff branch1 branch2 --stat               //显示出所有有差异的文件列表
Git diff branch1 branch2 -- 文件名(带路径)    //显示指定文件的详细差异
Git diff branch1 branch2                      //显示出所有有差异的文件的详细差异
git diff ffd98b b8e7b0 查看某两个版本之间的差异
git diff ffd98b:filename b8e7b0:filename 查看某两个版本的某个文件之间的差异

git diff FEA_v2.1_12721_ipsetHash master ./lw_ipset_ops.h > hns.patch
[root@localhost src]# git diff FEA_v2.1_12721_ipsetHash master ./lw_ipset_ops.h > hns.patch
[root@localhost src]# cat hns.patch

diff --git a/src/lw_ipset_ops.h b/src/lw_ipset_ops.h
index 3ab0671..aee4203 100755
--- a/src/lw_ipset_ops.h
+++ b/src/lw_ipset_ops.h
@@ -28,10 +28,10 @@ typedef struct _LW_SET_OPERATIONS { }
     int (*ElementDel)(void *, void *);
-    int (*Diff)(void *, void *, __inout struct list_head *);
+    int (*Diff)(void *, void *, __out struct file *);
     void (*Flush)(void *);


git submodule init
git submodule update