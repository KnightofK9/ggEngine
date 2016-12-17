function StageBlock() {
    var stageBlockPanel = $("#gg-stage-block");
    var navTab = $("#gg-stage-block-nav-tab");

    var stageBlockList = $("#gg-stage-block-list");
    var blockList = [];
    var stageList = [];
    var that = this;
    var blockId = 0;
    var stageId = 0;
    var drawBlockList = [];
    var addBlock = function(dialogRef,currentBlock){
        var name = dialogRef.getModalBody().find('#dialog-t1').val();
        var x = parseFloat(dialogRef.getModalBody().find('#dialog-n1').val());
        var y = parseFloat(dialogRef.getModalBody().find('#dialog-n2').val());
        var width = parseFloat(dialogRef.getModalBody().find('#dialog-n3').val());
        var height = parseFloat(dialogRef.getModalBody().find('#dialog-n4').val());
        if(!currentBlock){
            currentBlock = new CVBlock();
        }
        currentBlock.name = name;
        currentBlock.x = x;
        currentBlock.y = y;
        currentBlock.width = width;
        currentBlock.height = height;
        var isReplace = false;
        for(var i = 0; i <blockList.length; i++){
            if(blockList[i].name === currentBlock.name){
                blockList[i] = currentBlock;
                isReplace = true;
            }
        }
        if(!isReplace){
            blockList.push(currentBlock);
            createLine(currentBlock.name,true);
        }

    };
    var addStage = function(dialogRef,currentState){
        var name = dialogRef.getModalBody().find('#dialog-t1').val();
        if(!currentState){
            currentState = new CVStage();
        }
        currentState.name = name;
        var isReplace = false;
        for(var i = 0; i <stageList.length; i++){
            if(stageList[i].name === currentState.name){
                stageList[i] = currentState;
                isReplace = true;
            }
        }
        if(!isReplace){
            stageList.push(currentState)
            createLine(currentState.name,false);
        }
    };
    var createLine = function (name,isBlock) {
        var divClass = "list-group-item";
        var divId = "";
        if(isBlock) divId = "gg-block-id-";
        else{
            divId = "gg-stage-id-";
            divClass+=" list-group-item-info";
        }
        divId += name;
        var additionalOption = '<i onclick="stageBlock.onSelectViewClick(' + isBlock + ',\'' + name + '\')" class="glyphicon glyphicon-eye-open gg-hierarchy-view"></i>';
        if(!isBlock) additionalOption = "";
        var div = '<div id="'+divId+'" ><a  class="' + divClass + '">' + name
            + additionalOption
            + '<i onclick="stageBlock.onSelectLineClick(' + isBlock + ',\'' + name + '\')" class="glyphicon glyphicon-zoom-in gg-hierarchy-select"></i>'
            + '<i onclick="stageBlock.handleRemoveClick(' + isBlock + ',\'' + name + '\')" class="glyphicon glyphicon-remove gg-hierarchy-delete"></i>'
            + '</a></div>';
        stageBlockList.append(div);
        sortable('.sortable', {});
    };

    this.setActive = function (isActive) {
        if (isActive) {
            stageBlockPanel.css("display", "block");
            navTab.addClass("active");
        } else {
            stageBlockPanel.css("display", "none");
            navTab.removeClass("active");
        }
    };

    this.getBlockList = function(){
        return drawBlockList;
    };

    this.addBlock = function (currentBlock) {
        var label = 'Create';
        if(currentBlock) label = 'Update';
        BootstrapDialog.show({
            closable: true,
            title: "Add block",
            message: 'Name <input id="dialog-t1" type="text" class="form-control">'
            + 'x <input id="dialog-n1" type="number" class="form-control">'
            + 'y <input id="dialog-n2" type="number" class="form-control">'
            + 'Width <input id="dialog-n3" type="number" class="form-control">'
            + 'Height <input id="dialog-n4" type="number" class="form-control">'
            ,
            onshow: function (dialogRef) {
                var name = "Block";
                var x = 0;
                var y = 0;
                var width = 100;
                var height = 100;
                if(currentBlock){
                    name = currentBlock.name;
                    x = currentBlock.x;
                    y = currentBlock.y;
                    width = currentBlock.width;
                    height = currentBlock.height;
                }else{
                    name += blockId++;
                }
                dialogRef.getModalBody().find('#dialog-t1').val(name);
                dialogRef.getModalBody().find('#dialog-n1').val(x);
                dialogRef.getModalBody().find('#dialog-n2').val(y);
                dialogRef.getModalBody().find('#dialog-n3').val(width);
                dialogRef.getModalBody().find('#dialog-n4').val(height);

            },
            buttons: [{
                label: label,
                action: function (dialogRef,currentBlock) {
                    addBlock(dialogRef);
                    dialogRef.close();
                }
            }]
        });
    };
    this.addStage = function (currentStage) {
        var label = 'Create';
        if(currentStage) label = 'Update';
        BootstrapDialog.show({
            closable: true,
            title: "Add block",
            message: 'Name <input id="dialog-t1" type="text" class="form-control">'
            ,
            onshow: function (dialogRef) {
                var name = "Stage";
                if(currentStage){
                    name = currentStage.name;
                }else{
                    name += stageId++;
                }
                dialogRef.getModalBody().find('#dialog-t1').val(name);

            },
            buttons: [{
                label: label,
                action: function (dialogRef,currentStage) {
                    addStage(dialogRef);
                    dialogRef.close();
                }
            }]
        });
    };
    this.onSelectViewClick = function(isBlock,name){
        if(!isBlock) return;
        var block = null;
        for(var i = 0;  i<blockList.length; i++){
            if(blockList[i].name === name){
                block = blockList[i];
                break;
            }
        }
        var index = -1;
        for(var i = 0;i < drawBlockList.length; i++){
            if(drawBlockList[i].name === name){
                index = i;
                break;
            }
        }
        if(index > -1){
            drawBlockList.splice(index,1);
        }else{
            drawBlockList.push(block);
        }
        sceneEditor.editState.refreshDrawBlock();
    };
    this.onSelectLineClick = function(isBlock,name){
        var element = null;
        var array = stageList;
        if(isBlock){
            array = blockList;
        }
        for(var i = 0; i < array.length; i++){
            if(array[i].name == name){
                element = array[i];
                break;
            }
        }
        if(isBlock){
            that.addBlock(element);
        }else{
            that.addStage(element);
        }
    };
    this.handleRemoveClick = function(isBlock,name){
        var divId = "";
        if(isBlock) divId = "gg-block-id-";
        else{
            divId = "gg-stage-id-";
        }
        divId += name;
        var array = stageList;
        if(isBlock) array = blockList;
        for(var i = 0; i <array.length; i++){
            if(array[i].name === name){
                array.splice(i,1);
                break;
            }
        }
        $("#"+divId).remove();
    };
    this.reset = function(){
        stageBlockList.html("");
        blockList = [];
        stageList = [];
        blockId = 0;
        stageId = 0;
        drawBlockList = [];
    };
    var init = function () {
        that.reset();
        sortable('.sortable', {});
    };
    init();
}