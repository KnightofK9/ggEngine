/**
 * Created by Phan on 12/10/2016.
 */
function ObjectInfo(){
    var objectInfoPanel = $("#gg-object-info");
    var navTab = $("#gg-object-info-nav-tab");
    var currentInputHObject = null;
    var currentInput = null;
    var that = this;
    var timeOutId = 0;
    this.setActive = function(isActive){
        if(isActive){
            objectInfoPanel.css("display","block");
            navTab.addClass("active");
        }else{
            objectInfoPanel.css("display","none");
            navTab.removeClass("active");
        }
    };
    var onCompletedEditInput = function(){
        for(var key in currentInput){
            if(currentInput.hasOwnProperty(key)){
                var fieldName = currentInput[key][0].labels[0].textContent;
                var value = currentInput[key].val();
                if(!isNaN(value)){
                    currentInputHObject._item[fieldName] = parseFloat(value);
                }else{
                    currentInputHObject._item[fieldName] = value;
                }

            }
        }
    };
    var onInput = function(fieldName){
        var value = currentInput[fieldName].val();
        if(!isNaN(value)){
            currentInputHObject._item[fieldName] = parseFloat(value);
        }else{
            currentInputHObject._item[fieldName] = value;
        }
    };
    var init = function(){
        objectInfoPanel.keypress(function (e) {
            if (e.which == 13) {
                onCompletedEditInput();
                return false;
            }
            return true;
        });

        that.setShow(false);
    };
    var createInputField = function(fieldName,value){
        var optional = "";
        if(!isNaN(value)){
            optional = 'step="1"';
        }
        var div = '<label>'
        + fieldName
        +'<input id="gg-object-info-'+ fieldName +'" type="number" '+ optional +' class="form-control gg-object-info-input-field"></label>';
        objectInfoPanel.append(div);
        var curInput = $("#gg-object-info-"+fieldName);
        curInput.val(value);
        curInput.bind('keyup change click', function (e) {
            if (! curInput.data("previousValue") ||
                curInput.data("previousValue") != curInput.val()
            )
            {
                onInput(fieldName);
                curInput.data("previousValue", curInput.val());
            }

        });
        curInput.data("previousValue", curInput.val());


        currentInput[fieldName] = curInput;
    };

    this.setInputObject = function(hObject){
        that.reset();
        currentInputHObject = hObject;
        if(isNotNull(hObject._item.x)){
            createInputField("x",hObject._item.x);
        }
        if(isNotNull(hObject._item.y)){
            createInputField("y",hObject._item.y);
        }
        that.setShow(true);
    };
    this.reset = function(){
        currentInputHObject = null;
        currentInput = {};
        objectInfoPanel.html("");
    };
    this.setShow = function(isShow){
        if(isShow){
            objectInfoPanel.css("display","block");
        }else{
            objectInfoPanel.css("display","none");
        }
    };
    init();
}
function isNull(object){
    if (typeof object === "undefined" || object === null) {
       return true;
    }
    return false;
}
function isNotNull(object){
    return !isNull(object);
}