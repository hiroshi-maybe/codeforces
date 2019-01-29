function copyinput(info, tab) {
  chrome.tabs.sendMessage(tab.id, 'input');
}
function copyoutput(info, tab) {
  chrome.tabs.sendMessage(tab.id, 'output');
}
chrome.contextMenus.create({"title": "Copy input","onclick": copyinput});
chrome.contextMenus.create({"title": "Copy output","onclick": copyoutput});
