/**
 * Created by Knight of k9 on 11/11/2016.
 */
var ggConsole = new function(){
    var c = null;
    this.init = function(){
       c =  $("#gg-console");
    };
    this.log = function(message){
        c.html(c.html()+"</br>"+message);
    }
};