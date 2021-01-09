<template>
  <div id="stage3">
    <!--修改下方的MessageList和PostDialog-->
    <MessageList v-bind:messageList="messageList">
    </MessageList>
    <PostDialog v-bind:dialogVisible="dialogVisible" @add-message-child="addMessage" @close-dialog="closeDialog">
    </PostDialog>
  </div>
</template>

<script>
import MessageList from "@/components/MessageList.vue"
import PostDialog from "@/components/PostDialog.vue"

export default {
  name: 'Stage3',
  components: {
    MessageList,
    PostDialog
  },
  // 请在下方设计自己的数据结构和响应函数
  data(){
    return {
      messageList: [],
      dialogVisible: true,
    }
  },
  methods: {
        addMessage: function(title, content, user) {
            this.messageList.push({
                title: title,
                content: content,
                user: user,
                timestamp: Math.round((new Date()).getTime() / 1000)
            })
            this.closeDialog()
        },
        closeDialog: function() {
            this.dialogVisible = false
        }
    }
}
</script>