async function copyinout(info, tab) {
	await copyinput(info, tab);
	await delay();
	await copyoutput(info, tab);
}
// without delay >250(ms), second one is not copied to clipboard..
async function delay(info, tab) {
	return new Promise(r => setTimeout(r, 500));
}
async function copyinput(info, tab) {
	await copy(info, tab, "input");
}
async function copyoutput(info, tab) {
	await copy(info, tab, "output");
}
async function copy(info, tab, message) {
	return new Promise(resolve => {
		chrome.tabs.sendMessage(tab.id, message, (res) => {
			if (chrome.runtime.lastError) { alert(chrome.runtime.lastError); }
			resolve(res);
		});
	});
}

chrome.contextMenus.create({"title": "Copy both","onclick": copyinout});
chrome.contextMenus.create({"title": "Copy input","onclick": copyinput});
chrome.contextMenus.create({"title": "Copy output","onclick": copyoutput});
