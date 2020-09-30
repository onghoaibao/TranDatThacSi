
import random

print(random.randint(35, 120))


f = open("/home/ohbao/Desktop/Github/TranDatThacSi/Code/HTML/tabledata.html", 'r');

rs = f.readlines()
sOut = ""
for i in rs:
    sOut += i


listmac = ["ABCDEFABCDEF", "A1B2C3D4E5F6", "A1B2C3D4E5F8"]
mapName = {"ABCDEFABCDEF": "TB1", "A1B2C3D4E5F6": "TB2", "A1B2C3D4E5F8": "TB3"}


data = ""
dataOut = "" 
cou = 0
nLine = 0

for t in range(50):
    y = 0
    for i in listmac:
       
        k1 = 30
        k2 = 120
        t1 = random.randint(k1, k2)
        t2 = random.randint(k1, k2)
        t3 = random.randint(k1, k2)
        
        if (cou == 0):
            nLine = nLine + len(listmac)
            stt = str("<tr>") + str("<th>") + str(nLine) + str("</th>")
            sn = str("<th>") + str(mapName[i]) + str("</th>")
            s1 = str("<th style=\"background-color:#FF0000;\">" if 90 <= t1 else "<th style=\"background-color:#ff9900;\">" if 60 <= t1 else "<th style=\"background-color:#00cc00;\">") + str(t1) + str("</th>")
            s2 = str("<th style=\"background-color:#FF0000;\">" if 90 <= t2 else "<th style=\"background-color:#ff9900;\">" if 60 <= t2 else "<th style=\"background-color:#00cc00;\">") + str(t2) + str("</th>")
            s3 = str("<th style=\"background-color:#FF0000;\">" if 90 <= t3 else "<th style=\"background-color:#ff9900;\">" if 60 <= t3 else "<th style=\"background-color:#00cc00;\">") + str(t3) + str("</th>") 
            sr = str("<th rowspan=\"") + str(len(listmac)) + str("\">") + str("12:12:" + str("0" + str(t) if t+2 < 10 else t+2)) + str("</th>") + str("</tr>");
            data = data + stt + sn + str(s1) + str(s2) + str(s3) + sr;
            cou+=1;
        else:   
            y += 1
            stt = str("<tr>") + str("<th>") + str(nLine - y) + str("</th>")
            sn  =  str("<th>") + str(mapName[i]) + str("</th>")
            s1  = str("<th style=\"background-color:#FF0000;\">" if 90 <= t1 else "<th style=\"background-color:#ff9900;\">" if 60 <= t1 else "<th style=\"background-color:#00cc00;\">") + str(t1) + str("</th>")
            s2  = str("<th style=\"background-color:#FF0000;\">" if 90 <= t2 else "<th style=\"background-color:#ff9900;\">" if 60 <= t2 else "<th style=\"background-color:#00cc00;\">") + str(t2) + str("</th>")
            s3  = str("<th style=\"background-color:#FF0000;\">" if 90 <= t3 else "<th style=\"background-color:#ff9900;\">" if 60 <= t3 else "<th style=\"background-color:#00cc00;\">") + str(t3) 
            data = data + stt + sn + str(s1) + str(s2) + str(s3);
            cou+=1;
            if cou == len(listmac):
                dataOut = data + dataOut
                data = ""
                cou = 0
    if t%2 == 0:
        listmac = ["ABCDEFABCDEF", "A1B2C3D4E5F6"]
    else:
        listmac = ["ABCDEFABCDEF", "A1B2C3D4E5F6", "A1B2C3D4E5F8"]


print(len(sOut))
sOut = sOut.replace("[DATA_TEMP]", dataOut)
print(len(sOut))

f = open("/home/ohbao/Desktop/Github/TranDatThacSi/Code/HTML/tabledata_temp1.html", 'w');
f.write(sOut)

print("<th style=\"background-color:#FF0000;\">")