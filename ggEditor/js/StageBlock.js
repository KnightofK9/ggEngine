function StageBlock() {
    var stageBlockPanel = $("#gg-stage-block");
    var navTab = $("#gg-stage-block-nav-tab");

    var stageBlockList = $("#gg-stage-block-list");
    var blockStageList = [];
    var that = this;
    var createLine = function (id, name) {
        var divClass = "list-group-item";

        var div = '<div onclick="stageBlock.onSelectLineClick(' + id + ')" id="stage-block-' + id + '"><a  class="' + divClass + '">' + name
            + '<i onclick="stageBlock.handleRemoveClick(' + id + ')" class="glyphicon glyphicon-remove gg-hierarchy-delete"></i>'
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
    this.addBlock = function () {

    };
    this.addStage = function () {

    };
    this.onSelectLineClick = function(id){

    };
    this.handleRemoveClick = function(id){

    };
    this.reset = function(){
        stageBlockList.html("");
        blockStageList = [];
        createLine(1,2);
        createLine('a','b');
        createLine('c','d');
    };
    var init = function () {
        that.reset();
        sortable('.sortable', {});
    };
    init();
}