#ifndef __MAILCORE_MCMESSAGEBUILDER_H_

#define __MAILCORE_MCMESSAGEBUILDER_H_

#include <MailCore/MCBaseTypes.h>
#include <MailCore/MCAbstractMessage.h>

#ifdef __cplusplus

namespace mailcore {
	
	class Attachment;
    class HTMLRendererTemplateCallback;
	
	class MessageBuilder : public AbstractMessage {
	public:
		MessageBuilder();
		virtual ~MessageBuilder();
		
		virtual void setHTMLBody(String * htmlBody);
		virtual String * htmlBody();
		
		virtual void setTextBody(String * textBody);
		virtual String * textBody();
		
		virtual void setAttachments(Array * /* Attachment */ attachments);
		virtual Array * /* Attachment */ attachments();
		virtual void addAttachment(Attachment * attachment);
		
		// attachments (usually images) that are included in HTML.
		virtual void setRelatedAttachments(Array * /* Attachment */ attachments);
		virtual Array * /* Attachment */ relatedAttachments();
		virtual void addRelatedAttachment(Attachment * attachment);
		
		// When boundary needs to be prefixed (to go through spam filters).
		virtual void setBoundaryPrefix(String * boundaryPrefix);
		virtual String * boundaryPrefix();
		
		virtual Data * data();
        
        virtual String * htmlRendering(HTMLRendererTemplateCallback * htmlCallback = NULL);
        
    public: // subclass behavior
		MessageBuilder(MessageBuilder * other);
		virtual String * description();
		virtual Object * copy();
        
	private:
		String * mHTMLBody;
		String * mTextBody;
		Array * mAttachments;
		Array * mRelatedAttachments;
		String * mBoundaryPrefix;
		void init();
		Data * dataAndFilterBcc(bool filterBcc);
	};
	
};

#endif

#endif
