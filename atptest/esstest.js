let intervalId1;
let intervalId2;
let intervalId3;
let intervalconst = 2000;
let isRunning = false;

window.onload = function()
{
	cleartextarea()
	document.getElementById('EssExec').style.backgroundColor = 'orange';
}

function cleartextarea()
{
	document.getElementById('freeform').value = "";
	document.getElementById('EssExec').style.backgroundColor = 'orange';
}

function scrollToBottom()
{
	const thetextarea = document.getElementById('freeform');
	thetextarea.scrollTop = thetextarea.scrollHeight;
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
			{
				document.getElementById('freeform').value = document.getElementById('freeform').value + xmlHttp.responseText;
				scrollToBottom();
			}
    	}
    	xmlHttp.open("GET", theUrl, true); // true for asynchronous 
    	xmlHttp.send(null);
	}
}

function EssTestExecute() 
{
	var theIpAddress=document.getElementById('IpAddress').value;
	var TheMask=document.getElementById('Mask').value;
	var theUrl="http://" + theIpAddress + "/atp?tidMask=" + TheMask + "&stopOnErrMask=0";
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
				scrollToBottom();
			}

    	}
    	xmlHttp.open("GET", theUrl, true); // true for asynchronous 
    	xmlHttp.send(null);
		startLoop();
	}
}

function EssTestStopAll() 
{
	var theIpAddress=document.getElementById('IpAddress').value;
	var theUrl="http://" + theIpAddress + "/atpStop";
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
				scrollToBottom();
			}

    	}
    	xmlHttp.open("GET", theUrl, true); // true for asynchronous 
    	xmlHttp.send(null);
		stopLoop();
	}
}

function EssGetResults(tid_param)
{
	var theIpAddress=document.getElementById('IpAddress').value;
	var theUrlTid="http://" + theIpAddress + "/atpLogGet?tid=" + tid_param;
	var xmlHttp = new XMLHttpRequest();

	if (theIpAddress === "")
	{
		alert("IP Address is invalid");
	}
	else
	{
		xmlHttp.onreadystatechange = function() 
		{ 
			var jsonString;
        	if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
			{
				jsonString = xmlHttp.responseText;
				try 
				{
					const parsedData = JSON.parse(jsonString);
					const atpLogArray = parsedData.atpLogArray;
					//console.log("log array = ", atpLogArray);
					if (atpLogArray[1].TestID !== "0")
					{
						document.getElementById('freeform').value = document.getElementById('freeform').value + jsonString;
						document.getElementById('freeform').value = document.getElementById('freeform').value + "\n";
						scrollToBottom();
					}
					if ((atpLogArray[2].ErrorCode === "0") && (document.getElementById('EssExec').style.backgroundColor !== 'red'))
					{
						//console.log("ErrorCode = ", atpLogArray[2].ErrorCode);
						document.getElementById('EssExec').style.backgroundColor = 'green';
					}
					else
					{
						document.getElementById('EssExec').style.backgroundColor = 'red';
					}
				}
				catch (error)
				{
					console.error("Failed to parse JSON:", error);
				}
			}

    	}
    	xmlHttp.open("GET", theUrlTid, true); // true for asynchronous 
    	xmlHttp.send(null);
	}
}

function EssGetResults1()
{
	EssGetResults("1");
}

function EssGetResults2()
{
	EssGetResults("2");
}

function EssGetResults3()
{
	EssGetResults("3");
}

function startLoop()
{
	if(!isRunning)
	{
		isRunning = true;
		intervalId1 = setInterval(EssGetResults1, intervalconst);
		intervalId2 = setInterval(EssGetResults2, intervalconst);
		intervalId3 = setInterval(EssGetResults3, intervalconst);
	}
}

function stopLoop()
{
	if(isRunning)
	{
		isRunning = false;
		clearInterval(intervalId1);
		clearInterval(intervalId2);
		clearInterval(intervalId3);
	}
}

