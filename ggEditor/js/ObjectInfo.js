/**
 * Created by Phan on 12/10/2016.
 */
function ObjectInfo(){
    var objectInfoPanel = $("#gg-object-info");
    var navTab = $("#gg-object-info-nav-tab");
    var nameLabel = $("#gg-object-info-name");
    var currentInputHObject = null;
    var currentInput = null;
    var that = this;
    var timeOutId = 0;
    this.setActive = function(isActive){
        if(isActive){
            if(currentInputHObject !== null) objectInfoPanel.css("display","block");
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
    var onInput = function(fieldName,isExtraInfo){
        var value = currentInput[fieldName].val();
        var editItem = currentInputHObject._item;
        if(isExtraInfo){
            editItem = currentInputHObject._item.extraInfo;
        }
        if(value !== "" && !isNaN(value)){
            editItem[fieldName] = parseFloat(value);
        }else{
            if(fieldName == "dropType")
            {
                if(isNull(editItem[fieldName].type)) editItem[fieldName] = {};
                editItem[fieldName].type = value;
            }
            else{
                editItem[fieldName] = value;
            }
        }
    };
    var init = function(){
        // objectInfoPanel.keypress(function (e) {
        //     if (e.which == 13) {
        //         onCompletedEditInput();
        //         return false;
        //     }
        //     return true;
        // });

        that.setShow(false);
    };
    var createInputField = function(fieldName,value,isExtraInfo, isReadOnly){
        if(isNull(isReadOnly)) isReadOnly = false;
        if(isNull(isExtraInfo)) isExtraInfo = false;
        var optional = "";
        if(value !== "" &&!isNaN(value)){
            optional += 'type="number" step="1"';
        }else{
            optional += 'type="text"';
        }
        if(isReadOnly){
            optional += 'readonly="readonly"';
        }
        var div = '<label>'
        + fieldName
        +'<input id="gg-object-info-'+ fieldName +'" '+ optional +' class="form-control gg-object-info-input-field"></label>';
        objectInfoPanel.append(div);
        var curInput = $("#gg-object-info-"+fieldName);
        curInput.val(value);
        if(!isReadOnly){
            curInput.bind('keyup change click', function (e) {
                if (! curInput.data("previousValue") ||
                    curInput.data("previousValue") != curInput.val()
                )
                {
                    onInput(fieldName,isExtraInfo);
                    curInput.data("previousValue", curInput.val());
                }

            });

            curInput.data("previousValue", curInput.val());
        }



        currentInput[fieldName] = curInput;
    };

    this.setInputObject = function(hObject){
        that.reset();
        currentInputHObject = hObject;
        createInputField("Name",hObject._name,false,true);
        if(isNotNull(hObject._item.x)){
            createInputField("x",hObject._item.x);
        }
        if(isNotNull(hObject._item.y)){
            createInputField("y",hObject._item.y);
        }

        if(isNotNull(hObject._item.width)){
            createInputField("width",hObject._item.width);
        }
        if(isNotNull(hObject._item.height)){
            createInputField("height",hObject._item.height);
        }
        if(isNotNull(hObject._item.extraInfo)){
            if(isNotNull(hObject._item.extraInfo.dropType))
                createInputField("dropType",hObject._item.extraInfo.dropType.type,true);
        }
        that.setShow(true);
    };
    this.reset = function(){
        currentInputHObject = null;
        currentInput = {};
        that.setShow(false);
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