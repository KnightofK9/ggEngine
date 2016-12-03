/**
 * Created by Knight of k9 on 11/11/2016.
 */
var Helper = new function () {
    this.getRandomFloatInRange = function(min,max){
        return Math.random()*(max - min) + min;
    };
    this.getRandomIntInRange = function(min,max){
        return Math.floor(Math.random()*(max+1-min) +min);
    };
    this.downloadJson = function(json,name){
        var dataStr = "data:text/json;charset=utf-8," + encodeURIComponent(JSON.stringify(json));
        var dlAnchorElem = document.getElementById('downloadAnchorElem');
        dlAnchorElem.setAttribute("href",     dataStr     );
        dlAnchorElem.setAttribute("download", name + ".json");
        dlAnchorElem.click();
    };
    this.getBaseLog = function(x,y){
        return Math.log(y) / Math.log(x);
    };
    this.getJsonFromFile = function(file, callback){
        var uploadedFile = file;

        //if(uploadedFile.type !== "text/jso" && uploadedFile.type !== "application/x-javascript") {
        //    alert("Wrong file type == " + uploadedFile.type);
        //    callback(false,null);
        //    return false;
        //}

        if (uploadedFile) {
            var readFile = new FileReader();
            readFile.onload = function(e) {
                var contents = e.target.result;
                var json = JSON.parse(contents);
                callback(true,json);
            };
            readFile.readAsText(uploadedFile);
        } else {
            console.log("Failed to load file");
            callback(false,null);
        }

    };

    this.createWrapLegend = function(name,content){
        return '<fieldset class="scheduler-border">'
            +'<legend class="scheduler-border">' + name + '</legend>'
            + content
            +'</fieldset>'
    };
};