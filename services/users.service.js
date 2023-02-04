var checkUserAddon = require('bindings')('checkuser');

function CheckUserService(){
}

CheckUserService.prototype.check = function(username){
//    return true;
    return checkUserAddon.checkUser(username);
}

module.exports = CheckUserService