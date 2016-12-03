/**
 * Created by Knight of k9 on 15/11/2016.
 */
function StateInfo(){
    var statePanel = $("#gg-state-info");
    var navTab = $("#gg-state-info-nav-tab");
    var useQuadTree = $("#gg-state-info-enable-quad-tree");
    var putEnemyToQuadTree = $("#gg-state-info-put-enemy-to-quad-tree");
    var renderStaticBody = $("#gg-state-info-render-static-body");

    var isRenderStaticBody = renderStaticBody.is(":checked");
    this.setActive = function(isActive){
        if(isActive){
            statePanel.css("display","block");
            navTab.addClass("active");
        }else{
            statePanel.css("display","none");
            navTab.removeClass("active");
        }
    };
    this.isUsedQuadTree = function(){
        return useQuadTree.is(":checked");
    };
    this.isPutEnemyToQuadTree = function(){
        return putEnemyToQuadTree.is(":checked");
    };
    this.isRenderStaticBody = function(){
        return isRenderStaticBody;
    };
    var renderStaticBodyToggle = function(){
        isRenderStaticBody = renderStaticBody.is(":checked");
    };
    renderStaticBody.change(function(){
        renderStaticBodyToggle();
    });

}

