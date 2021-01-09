<template>
  <div id="message-list">
    <!--请修改这两行注释中间的代码，达到用多个MessageBlock来展示messageList数据的效果-->
    <MessageBlock v-for="block in messageList" v-bind:key="block.timestamp" :title="block.title" :content="block.content" :user="block.user" :timestamp="block.timestamp">
    </MessageBlock>
    <!--请修改这两行注释中间的代码，达到用多个MessageBlock来展示messageList数据的效果-->
  </div>
</template>

<script>
import MessageBlock from "@/components/MessageBlock"

export default {
  name: "MessageList",
  components: {
    MessageBlock
  },
  props: {
    messageList: {
      type: Array,
      default: () => new Array(5).fill({
        title: "Hello",
        content: "Hello World!",
        user: "unknown",
        timestamp: Math.round((new Date()).getTime() / 1000)
      })
    }
  }
}
</script>
