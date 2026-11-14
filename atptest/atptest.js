window.onload = function()
{
	cleartextarea()
}
function cleartextarea()
{
	document.getElementById('freeform').value = ""
}
function Hello() 
{
	var theIpAddress=document.getElementById('IpAddress').value;
	var theUrl="http://" + theIpAddress + "/hello";
	var xmlHttp = new XMLHttpRequest();
	if (theIpAddress === "")
	{
		alert("IP Address is invalid");
	}
	else
	{
		xmlHttp.onreadystatechange = function() 
		{ 
        	if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
				document.getElementById('freeform').value = document.getElementById('freeform').value + xmlHttp.responseText;
    	}
    	xmlHttp.open("GET", theUrl, true); // true for asynchronous 
    	xmlHttp.send(null);
	}
}

function AtpTestExecute() 
{
//	document.getElementById('freeform').value = "TEST"
//	Test 01:
	var theIpAddress=document.getElementById('IpAddress').value;
	var cextractNameTest="something:12:34:35:56:65:70:88:99:21:23:36";
	var theUrlcextractNameTest="http://" + theIpAddress + "/cextractfile?name=" + cextractNameTest;
	var xmlHttp = new XMLHttpRequest();
	if (theIpAddress === "")
	{
		alert("IP Address is invalid");
	}
	else
	{
		xmlHttp.onreadystatechange = function() 
		{ 
        	if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
			{
				document.getElementById('freeform').value = document.getElementById('freeform').value + xmlHttp.responseText;
				document.getElementById('freeform').value = document.getElementById('freeform').value + "\n";
				AtpTest02();
			}

//			console.log("DEBUG Status: ", xmlHttp.status);
//			console.log("DEBUG Response Text: ", xmlHttp.responseText);
    	}
    	xmlHttp.open("GET", theUrlcextractNameTest, true); // true for asynchronous 
    	xmlHttp.send(null);
	}
}
function AtpTest02() 
{
	var theIpAddress=document.getElementById('IpAddress').value;
	var cextractNameTest="something:12:34:35:56:65:70:88:99:21:23:36";
	var theUrl="http://" + theIpAddress + "/cparseparam?name=" + cextractNameTest;
	var xmlHttp = new XMLHttpRequest();
	if (theIpAddress === "")
	{
		alert("IP Address is invalid");
	}
	else
	{
		xmlHttp.onreadystatechange = function() 
		{ 
        	if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
			{	
				document.getElementById('freeform').value = document.getElementById('freeform').value + xmlHttp.responseText;
				document.getElementById('freeform').value = document.getElementById('freeform').value + "\n";
				AtpTest03();
			}

    	}
    	xmlHttp.open("GET", theUrl, true); // true for asynchronous 
    	xmlHttp.send(null);
	}
}
function AtpTest03() 
{
	var theIpAddress=document.getElementById('IpAddress').value;
	var NameTest="1&pinNo=1&state=1";
	var theUrl="http://" + theIpAddress + "/sbcGpioStateSet?bankNo=" + NameTest;
	var xmlHttp = new XMLHttpRequest();
	if (theIpAddress === "")
	{
		alert("IP Address is invalid");
	}
	else
	{
		xmlHttp.onreadystatechange = function() 
		{ 
        	if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
			{	
				document.getElementById('freeform').value = document.getElementById('freeform').value + xmlHttp.responseText;
				document.getElementById('freeform').value = document.getElementById('freeform').value + "\n";
				//AtpTest04();
			}

    	}
    	xmlHttp.open("GET", theUrl, true); // true for asynchronous 
    	xmlHttp.send(null);
	}
}
