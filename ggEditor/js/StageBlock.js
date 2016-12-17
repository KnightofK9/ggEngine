function StageBlock(){
    var stageBlockPanel = $("#gg-stage-block");
    var navTab = $("#gg-stage-block-nav-tab");
    this.setActive = function(isActive){
        if(isActive){
            stageBlockPanel.css("display","block");
            navTab.addClass("active");
        }else{
            stageBlockPanel.css("display","none");
            navTab.removeClass("active");
        }
    };
}