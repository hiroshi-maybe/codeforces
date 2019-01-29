
function copyToClipboard(str) {
	const el = document.createElement('textarea');
	el.value = str;
	document.body.appendChild(el);
	el.select();
	document.execCommand('copy');
	document.body.removeChild(el);
}

function formatInputSamples(data) {
	var sep = "~\n";
	return data.join(sep)+sep;
}

function formatOutputSamples(data) {
	return data.join("");
}

chrome.runtime.onMessage.addListener(function(message, sender, sendResponse) {
	var es = document.querySelectorAll("div.sample-test ."+message+" pre");	
	var data = Array.from(es).map(x => x.innerText);
	data = message==="input"?formatInputSamples(data):formatOutputSamples(data);
	copyToClipboard(data);
//	alert(message+" successfully copied!\n"+data);
});
