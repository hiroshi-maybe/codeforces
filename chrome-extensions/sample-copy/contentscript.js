async function copyToClipboard(str) {
	try {
    	await navigator.clipboard.writeText(str);
	} catch (err) {
    	alert('Failed to copy: ', err);
	}

	return str;
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
	const batchsample = message==="input"?formatInputSamples(data):formatOutputSamples(data);

	(async () => {
		const data = await copyToClipboard(batchsample);
		console.log("Copied", data);
		sendResponse(data);
	})();
	return true;
});
