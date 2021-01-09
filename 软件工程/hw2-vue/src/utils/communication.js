/**
 * 如果需要修改为正常上线模式，请注释下面mock的import代码
 * **/
//import "@/mock/index"

const { default: API } = require("./API")

 // 请在下方实现自己的后端通信函数
function getAllMessage() {
    var request = new XMLHttpRequest()
    var jsonList
    request.open(API.GET_MESSAGE_LIST.method, API.GET_MESSAGE_LIST.path, false)
    request.onreadystatechange = function () {
        if(request.readyState === 4 && request.status === 200){
            jsonList = JSON.parse(request.responseText)["data"];
        } else {
            jsonList = []
        }
    }
    request.send()
    return jsonList
}

function sendNewMessage(title, content, user) {
    var request = new XMLHttpRequest()
    var success = false
    request.open(API.POST_NEW_MESSAGE.method, API.POST_NEW_MESSAGE.path, false)
    request.onreadystatechange = function () {
        if(request.readyState === 4 && request.status === 201){
            success = true
        } else {
            success = false
        }
    }
    document.cookie = "user=" + user
    request.send(JSON.stringify({
        "title": title,
        "content": content,
    }))
    return success
}

function getCookie(cookie, key){
    var getMatchCookie;
    var arrCookie = cookie.split(";");
    key = key.replace(/(^\s*)|(\s*$)/g, "")
    for(var i=0;i < arrCookie.length;i++){
         var arr = arrCookie[i].split("=");
         if(key == arr[0].replace(/(^\s*)|(\s*$)/g, "")){
            getMatchCookie = arr[1];
            break;
         }
    }
    return getMatchCookie;
}

export {getAllMessage, sendNewMessage, getCookie};
